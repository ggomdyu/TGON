/*
* Author : Junho-Cha
* Date : 02/08/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "Interface/IModule.h"

#include <atomic>
#include <thread>
#include <mutex>
#include <deque>

namespace tgon
{


class TGON_API TWorkThreadModule :
	public IModule
{
	using WorkPool = std::deque<std::function<void( )>>;
	using ThreadPool = std::deque<std::thread>;

/*
	Generator
*/
public:
	TGON_MAKE_OBJECT_INTERFACE( TWorkThreadModule )

/*
	Cons/Destructor
*/
public:
	//
	// Initialize thread module.
	// Make thread as much as hardware thread supports
	//
	// @param numThread Number of thread you want to use
	//
	explicit TWorkThreadModule( std::size_t numThread = std::thread::hardware_concurrency( ));
	virtual ~TWorkThreadModule( );


/*
	Commands
*/
public:
	//
	// Enqueue the work. The idle thread will execute the work.
	//
	// @param workFunc Work which you want to register to work pool
	// @param workFuncArgs workFunc's parameter list
	//
	template <class WorkFunc, class... WorkFuncArgs>
	void Request( WorkFunc&& workFunc, WorkFuncArgs&&... workFuncArgs );

	//
	// Wait until the work threads finished all of works.
	//
	void Wait( );


/*
	Internal works
*/
private:
	void JoinAll( );

	void InfiniteLoop( );


/*
	Private variables
*/
private:
	bool m_isDestroying;
	std::atomic_uint m_workingCount;
	WorkPool m_workQueue;
	ThreadPool m_threadQueue;
	std::mutex m_mutex;
	std::condition_variable m_waitCv;
	std::condition_variable m_finishCv;
};


template <class WorkFunc, class... WorkFuncArgs>
void tgon::TWorkThreadModule::Request( WorkFunc&& workFunc, WorkFuncArgs&&... workFuncArgs )
{
	std::unique_lock<std::mutex> lock( m_mutex );

	m_workQueue.emplace_back( std::forward<WorkFunc>( workFunc ), std::forward<WorkFuncArgs>( workFuncArgs )... );
	
	// Wake up one thread
	m_waitCv.notify_one( );
}


}