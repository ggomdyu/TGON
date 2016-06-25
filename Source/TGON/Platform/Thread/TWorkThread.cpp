#include "PrecompiledHeader.h"
#include "TWorkThread.h"


tgon::TWorkThread::TWorkThread( std::size_t numThread ) :
	m_isDestroying( false ),
	m_currWorkCount( 0 )
{
	for ( std::size_t i =0; i < numThread; ++i )
	{
		m_threadQueue.push_back(
			std::thread( &TWorkThread::InfiniteLoop, this )
		);
	}
}

tgon::TWorkThread::~TWorkThread( )
{
	std::unique_lock<std::mutex> lock( m_mutex );

	m_isDestroying = true;
	m_waitCv.notify_all( );
	lock.unlock( );

	this->JoinAll( );
}

void tgon::TWorkThread::JoinAll( )
{
	for ( auto& elem : m_threadQueue )
	{
		elem.join( );
	}
}

void tgon::TWorkThread::Wait( )
{
	std::unique_lock<std::mutex> lock( m_mutex );
	m_finishCv.wait( lock,
		// Wait until all of works are finished..
		[this]( )
		{
			return ( m_currWorkCount == 0 ) &&
				( m_workQueue.empty( ));
		}
	);
}

void tgon::TWorkThread::InfiniteLoop( )
{
	while ( true )
	{
		std::unique_lock<std::mutex> lock( m_mutex );
		m_waitCv.wait( lock,
			// m_waitCv will wake up one thread when these conditions return true.
			[this]( )
			{ 
				return ( m_isDestroying || 
					!m_workQueue.empty( )); 
			}
		);

		if ( !m_workQueue.empty( ))
		{
			/*
				START
			*/
			++m_currWorkCount;

			// Get the work and pop
			auto poppedWork = m_workQueue.front( );
			m_workQueue.pop_front( );

			// Unlock mutex for the other thread's running.
			lock.unlock( );
			poppedWork( );


			/*
				FINISH
			*/
			--m_currWorkCount;
			m_finishCv.notify_one( );
		}
		else if ( m_isDestroying )
		{
			break;
		}
	}
}