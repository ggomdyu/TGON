#pragma once
#include "TThreadPool.h"


template <class T, class... Args>
void tgon::TThreadPool::Request( T&& f, Args&&... args )
{
	std::lock_guard<std::mutex> lock( m_mutex );

	m_taskQueue.emplace_back(
			std::forward<T>( f ), std::forward<Args>( args )...
		);

	m_waitCv.notify_one( ); // Wake up one thread
}