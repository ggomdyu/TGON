/**
 * @file    DispatchQueue.h
 * @author  ggomdyu
 * @since   05/23/2019
 */

#pragma once
#include <cstdint>
#include <thread>
#include <deque>
#include <mutex>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Core/Delegate.h"

namespace tgon
{

class TGON_API DispatchQueue final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit DispatchQueue(int32_t threadPoolCount = 1);
    
/**@section Destructor */
public:
    ~DispatchQueue();

/**@section Method */
public:
    void AddAsyncTask(const Delegate<void()>& task);
    
private:
    void DispatchQueueHandler();

/**@section Variable */
private:
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::deque<std::thread> m_threadPool;
    std::deque<Delegate<void()>> m_taskPool;
    bool m_needToDestroy;
};
    
} /* namespace tgon */