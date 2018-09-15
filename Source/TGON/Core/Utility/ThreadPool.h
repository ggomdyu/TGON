/**
 * @file    ThreadPool.h
 * @author  ggomdyu
 * @since   06/23/2018
 */

#pragma once
#include <deque>
#include <future>
#include <thread>
#include <mutex>

#include "Core/Object/Delegate.h"

namespace tgon
{

class ThreadPool
{
/**@section Private class */
private:
    class ThreadWorker;

    template <typename _ValueType>
    class ThreadWorkQueue :
        private std::deque<_ValueType>
    {
    /**@section Private type */
    private:
        using SuperType = std::deque<_ValueType>;

    /**@section Public method */
    public:
        template <typename _ValueType2>
        void Enqueue(_ValueType2&& value);

        _ValueType Dequeue();

        void Clear();

        bool IsEmpty() const;

    /**@section Private variable */
    private:
        mutable std::mutex m_mutex;
    };

/**@section Public constructor */
public:
    explicit ThreadPool(int32_t allocateThreadCount = std::min(std::thread::hardware_concurrency() - 1u, 1u));

/**@section Public method */
public:
    /**
     * @brief               Inserts a task to execute asynchronously by task threads.
     * @param [in] task     Task to execute asynchronously by task threads.
     * @param [in] args     Arguments of task function.
     * @return              
     */
    template <typename _TaskType, typename... _ArgTypes>
    auto AddTask(_TaskType&& task, _ArgTypes&&... args) -> std::future<decltype(task(std::forward<_ArgTypes>(args)...))>;

    /**
     * @brief   Waits until all thread execution has completed.
     * @detail  This function must be called before destroying ThreadPool. After invoke this, then
                ThreadPool class could be destructed safely.
     */
    void Join();

    /**
     * @brief   Checks all thread execution has completed.
     * @return  True if all thread execution has completed, false otherwise. 
     */
    bool IsJoinable() const noexcept;

/**@section Private variable */
private:
    /**@brief   The pool of threads. */
    std::vector<std::thread> m_threads;

    std::mutex m_conditionMutex;
    std::condition_variable m_conditionLock;

    /**@brief   The queue of task that used on task management. */
    std::mutex m_taskQueueMutex;
    ThreadWorkQueue<std::function<void()>> m_taskQueue;

    bool m_isJoinable;
};

template <typename _TaskType, typename... _ArgTypes>
auto ThreadPool::AddTask(_TaskType&& task, _ArgTypes&&... args) -> std::future<decltype(task(std::forward<_ArgTypes>(args)...))>
{
    using TaskReturnType = decltype(task(std::forward<_ArgTypes>(args)...));

    auto promise = std::make_unique<std::promise<TaskReturnType>>();
    std::future<TaskReturnType> future = promise->get_future();
    std::function<void()> wrappedTask([promise2 = std::move(promise)]()
    {
    });

    // Push the task to queue.
    m_taskQueue.Enqueue(wrappedTask);

    // Notify one thread that task exists.
    m_conditionLock.notify_one();
    
    return {};
}

template <typename _ValueType>
template <typename _ValueType2>
inline void ThreadPool::ThreadWorkQueue<_ValueType>::Enqueue(_ValueType2&& value)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    SuperType::push_back(std::forward<_ValueType2>(value));
}

template <typename _ValueType>
inline _ValueType ThreadPool::ThreadWorkQueue<_ValueType>::Dequeue()
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    
    _ValueType ret = std::move(SuperType::front());
    SuperType::pop_front();

    return std::move(ret);
}

template <typename _ValueType>
inline void ThreadPool::ThreadWorkQueue<_ValueType>::Clear()
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);

    SuperType::clear();
}

template <typename _ValueType>
inline bool ThreadPool::ThreadWorkQueue<_ValueType>::IsEmpty() const
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    return SuperType::empty();
}

} /* namespace tgon */