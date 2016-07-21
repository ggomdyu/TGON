// TGON.TestConsole.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "PrecompiledHeader.h"

#include <iostream>
#include <GameCore/Module/TWorkThreadModule.h>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <boost/lexical_cast.hpp>

using namespace tgon;


class TWorkThread
{
	// It's not thread-safe, so we using mutex on here
	using WorkQueue = std::deque<std::function<void( )>>;

	using ThreadQueue = std::vector<std::thread>;

public:
	TWorkThread( int threadNum = std::thread::hardware_concurrency() ) :
		m_workCount( 0 )
	{
		for ( int i = 0; i < threadNum; ++i )
		{
			m_threadQueue.push_back( std::thread( &TWorkThread::InfiniteLoop, this ) );
		}
	}

	void Wait( )
	{
		std::unique_lock<std::mutex> lock( m_mutex );
		m_finishConditionVar.wait( lock,
			[this]( ) { return ( m_workCount == 0 &&
				m_workQueue.empty( ) ); }
		);
	}

	void InfiniteLoop( )
	{
		while ( true )
		{
			std::unique_lock<std::mutex> lock( m_mutex );

			if ( !m_workQueue.empty( ))
			{
				auto work = m_workQueue.front( );
				m_workQueue.pop_front( );
			
				lock.unlock( );

				++m_workCount;
				work( );
				--m_workCount;

				m_finishConditionVar.notify_one( );
			}
		}
	}

	// Enqueue the work. The idle thread will execute the work.
	template <typename _FuncTy, typename... _FuncArgs>
	void Request( _FuncTy&& f, _FuncArgs&&... args )
	{
		m_workQueue.emplace_back( 
			std::forward<_FuncTy>( f ), 
			std::forward<_FuncArgs>( args )... 
		);
		
		m_waitConditionVar.notify_one( );
	}

private:
	std::atomic<int> m_workCount;
	WorkQueue m_workQueue;
	ThreadQueue m_threadQueue;
	std::mutex m_mutex;
	std::condition_variable m_waitConditionVar;
	std::condition_variable m_finishConditionVar;
};


int main()
{
	/*TWorkThread tt;
	DWORD b = GetTickCount( );

	std::atomic<int> v = 0;
	auto work = [&]( )
	{
		int temp = 0;
		for ( int i = 0 ; i < 25000000; ++i )
			temp += 1;

		v += temp;
	};

	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	tt.Request( work );
	
	std::cout << "b";
	tt.Wait( );
	std::cout << "a";

	DWORD e = GetTickCount( ) - b;

	std::cout << v;

	Sleep( 10000 );

	std::cout << v.load( ) << ", 걸린 시간: " << e;


	return  0;*/
	{

	TWorkThreadModule tw;

	DWORD b = GetTickCount( );

	std::atomic<int> v = 0;
	auto work = [&]( )
	{
		int temp = 0;
		for ( int i = 0; i < 25000000; ++i )
			temp += 1;

		v += temp;
	};

	tw.Request( work );
	tw.Request( work );
	tw.Request( work );
	tw.Request( work );
	tw.Request( work );
	tw.Request( work );
	tw.Request( work );
	tw.Request( work );

	std::cout << "a";
	tw.Wait( );
	std::cout << "b";



	DWORD e = GetTickCount( ) - b;

	
	std::cout << v << " "<<e << std::endl;
	}



    return 0;
}

