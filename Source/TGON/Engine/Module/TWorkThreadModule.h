/*
* Author : Junho-Cha
* Date : 02/08/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "Interface/IModule.h"


namespace tgon
{


class TGON_API TWorkThreadModule :
	public IModule
{
	using WorkQueue = std::deque<std::function<void()>>;

	using ThreadQueue = std::deque<std::thread>;

public:
	TGON_OBJECT( TWorkThreadModule, IModule )

public:
	/*
		Cons/Destructor
	*/
	// Fill the thread queue.
	explicit TWorkThreadModule( std::size_t numThread = std::thread::hardware_concurrency( ));
	
	virtual ~TWorkThreadModule( );

public:
	/*
		Commands
	*/
	// Enqueue the work. The idle thread will execute the work.
	template <class _FuncTy, class... _Args>
	void Request( _FuncTy&& work, _Args&&... args );

	// Wait until the work threads finished all of works
	void Wait( );


private:
	void JoinAll( );

	void InfiniteLoop( );


private:
	bool m_isDestroying;

	std::atomic_uint m_workingCount;

	WorkQueue m_workQueue;

	ThreadQueue m_threadQueue;

	std::mutex m_mutex;

	std::condition_variable m_waitCv;

	std::condition_variable m_finishCv;
};


template <class _FuncTy, class... _Args>
void tgon::TWorkThreadModule::Request( _FuncTy&& work,  _Args&&... args )
{
	std::unique_lock<std::mutex> lock( m_mutex );

	m_workQueue.emplace_back( std::forward<_FuncTy>( work ), std::forward<_Args>( args )... );
	
	// Wake up one thread
	m_waitCv.notify_one( );
}


}