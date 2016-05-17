/*
* Author : Junho-Cha
* Date : 02/08/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <deque>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <stdint.h>

namespace tgon
{


class TThreadPool final
{
	typedef std::deque<std::function<void()>> task_queue;
	typedef std::deque<std::thread> thread_queue;

public:
	// Make thread as mush as core count
	TThreadPool( std::size_t numThread = std::thread::hardware_concurrency( ));
	~TThreadPool( );

public:
	template <class T, class... Args>
	void Request( T&& f, Args&&... args );

	void Wait( );

private:
	void JoinAll( );
	void InfiniteLoop( );

private:
	std::atomic_uint m_workCount;

	task_queue m_taskQueue;
	thread_queue m_threadQueue;

	std::mutex m_mutex;
	std::condition_variable m_waitCv;
	std::condition_variable m_finishCv;
	bool m_isStop;
};


}

#include "TThreadPool.hpp"