/*
* Author : Junho-Cha
* Date : 02/08/2016
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


class TWorkThreadModule final
{
	// It's not thread-safe, so we using mutex on here
	using WorkQueue = std::deque<std::function<void()>>;
	using ThreadQueue = std::deque<std::thread>;

public:
	// Allocate thread ( default: Make as much as core count )
	explicit TWorkThreadModule( std::size_t numThread = std::thread::hardware_concurrency( ));
	~TWorkThreadModule( );

	// Enqueue the work. The idle thread will execute the work.
	template <class T, class... Args>
	void Request( T&& f, Args&&... args );

	// Wait until the work threads finished all of works
	void Wait( );

private:
	void JoinAll( );
	void InfiniteLoop( );

private:
	bool m_isDestroying;
	std::atomic_uint m_currWorkCount;
	WorkQueue m_workQueue;
	ThreadQueue m_threadQueue;
	std::mutex m_mutex;
	std::condition_variable m_waitCv;
	std::condition_variable m_finishCv;
};


template <class T, class... Args>
void tgon::TWorkThreadModule::Request( T&& f, Args&&... args )
{
	std::lock_guard<std::mutex> lock( m_mutex );

	m_workQueue.emplace_back(
			std::forward<T>( f ), std::forward<Args>( args )...
		);

	m_waitCv.notify_one( ); // Wake up one thread
}


}