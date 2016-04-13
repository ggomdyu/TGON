#include "PrecompiledHeader.h"
#include "TThreadPool.h"


tgon::TThreadPool::TThreadPool( std::size_t numThread ) :
	m_isStop( false ),
	m_waitCv( ),
	m_finishCv( ),
	m_workCount( )
{
	for ( std::size_t i =0; i <numThread; ++i )
	{
		m_threadQueue.push_back(
				std::thread( &TThreadPool::InfiniteLoop, this )
			);
	}
}

tgon::TThreadPool::~TThreadPool( )
{
	std::unique_lock<std::mutex> lock( m_mutex );

	m_isStop = true;
	m_waitCv.notify_all( );
	lock.unlock( );

	this->JoinAll( );
}

void tgon::TThreadPool::JoinAll( )
{
	for ( auto& elem : m_threadQueue )
	{
		elem.join( );
	}
}

void tgon::TThreadPool::Wait( )
{
	std::unique_lock<std::mutex> lock( m_mutex );
	m_finishCv.wait( lock,
					[this]( ){ return ( m_workCount == 0 ) && ( m_taskQueue.empty( )); }
			);
}

void tgon::TThreadPool::InfiniteLoop( )
{
	while ( true )
	{
		std::unique_lock<std::mutex> lock( m_mutex );
		m_waitCv.wait( lock,
					[this]( ){ return ( m_isStop || !m_taskQueue.empty( )); }
			);

		if ( !m_taskQueue.empty( ))
		{
			/*
				Starting work
			*/
			++m_workCount;

			auto task = m_taskQueue.front( );
			m_taskQueue.pop_front( );

			lock.unlock( );	// Unlock mutex for the other thread's running.
			task( );

			/*
				Finishing work
			*/
			--m_workCount;
			m_finishCv.notify_one( );
		}
		else if ( m_isStop )
		{
			break;
		}
	}
}