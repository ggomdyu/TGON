#include "PrecompiledHeader.h"

#include "TGON.h"

#include "TestScene.h"

#include <boost/property_tree/ptree.hpp>

#include <queue>
#include <future>
#include <thread>
#include <mutex>
#include <tuple>

using namespace tgon;

template <typename>
class PackagedTask;

template <typename _ReturnType, typename... _ArgTypes>
class PackagedTask<_ReturnType(_ArgTypes...)> final
{
public:
    template <typename _TaskType>
    explicit PackagedTask(_TaskType&& task);

public:
    const Delegate<_ReturnType(_ArgTypes...)>& GetTask() const noexcept;
    Delegate<_ReturnType(_ArgTypes...)>& GetTask() noexcept;

    std::future<_ReturnType> GetFuture();

private:
    Delegate<_ReturnType(_ArgTypes...)> m_task;
    std::promise<_ReturnType> m_promise;
};

template <typename _ReturnType, typename... _ArgTypes>
template <typename _TaskType>
inline PackagedTask<_ReturnType(_ArgTypes...)>::PackagedTask(_TaskType&& task) :
    m_task(std::forward<_TaskType>(task))
{
}

template <typename _ReturnType, typename ..._ArgTypes>
inline const Delegate<_ReturnType(_ArgTypes...)>& PackagedTask<_ReturnType(_ArgTypes...)>::GetTask() const noexcept
{
    return m_task;
}

template <typename _ReturnType, typename ..._ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& PackagedTask<_ReturnType(_ArgTypes...)>::GetTask() noexcept
{
    return m_task;
}

template<typename _ReturnType, typename... _ArgTypes>
inline std::future<_ReturnType> PackagedTask<_ReturnType(_ArgTypes...)>::GetFuture()
{
    return m_promise.get_future();
}

class ThreadPool;
class ThreadWorker
{
/* @section Public constructor */
public:
    explicit ThreadWorker(ThreadPool& owner);

/* @section Public operator */
public:
    void operator()();

/* @section Private variable */
private:
    ThreadPool& m_owner;
};

class ThreadPool
{
/* @section Public constructor */
public:
    explicit ThreadPool(int32_t allocateThreadCount = std::min(std::thread::hardware_concurrency() - 1u, 1u));

/* @section Public destructor */
public:
    ~ThreadPool();

/* @section Public method */
public:
    template <typename _ReturnType, typename... _ArgTypes>
    std::future<_ReturnType> AddTask(Delegate<_ReturnType(_ArgTypes...)> task, _ArgTypes&&... args);

    void Join();

    bool IsJoinable() const noexcept;

/* @section Private variable */
private:
    std::vector<std::thread> m_threads;
    std::mutex m_conditionalMutex;
    std::condition_variable m_conditionalLock;

    std::queue<Delegate<void()>> m_tasks;

    bool m_isJoinable;
};

ThreadPool::ThreadPool(int32_t allocateThreadCount) :
    m_threads(allocateThreadCount),
    m_isJoinable(true)
{
    for (auto& thread : m_threads)
    {
        thread = std::thread(ThreadWorker(*this));
    }
}

ThreadPool::~ThreadPool()
{
    if (this->IsJoinable())
    {
        this->Join();
    }
}

void ThreadPool::Join()
{
    m_isJoinable = false;
    m_conditionalLock.notify_all();

    for (auto& thread : m_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

bool ThreadPool::IsJoinable() const noexcept
{
    return m_isJoinable;
}

template<typename _ReturnType, typename... _ArgTypes>
std::future<_ReturnType> ThreadPool::AddTask(Delegate<_ReturnType(_ArgTypes...)> task, _ArgTypes&&... args)
{
    auto packagedTask = PackagedTask<_ReturnType()>([task, args...]()
    {
        task(args...);
    });

    auto future = packagedTask.GetFuture();

    m_tasks.push(std::move(packagedTask));

    m_conditionalLock.notify_one();

    return future;
}

ThreadWorker::ThreadWorker(ThreadPool& owner) :
    m_owner(owner)
{
}

inline void ThreadWorker::operator()()
{
   /* while (true)
    {

    }*/
}

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public destructor */
public:
    virtual ~ThousandParty() = default;

/* @section Public event handler */
public:
    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
        this->AddModule<TimeModule>();
        this->AddModule<SceneManagementModule>(std::make_unique<TestScene>(), VideoMode{}, Application::GetInstance()->GetRootWindow());

        ThreadPool tp(3);
        auto future = tp.AddTask(Delegate<int(int)>([](int v)
        {
            return 3;
        }), 5);
    }
    
    virtual void OnWillTerminate() override
    {
        SuperType::OnWillTerminate();
    }
    
/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

