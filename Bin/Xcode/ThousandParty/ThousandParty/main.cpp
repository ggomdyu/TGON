#include "PrecompiledHeader.h"

#include "TGON.h"

#include "TestScene.h"

#include <boost/property_tree/ptree.hpp>

#include "Core/Utility/ThreadPool.h"

using namespace tgon;



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
    ThousandParty() : tp(3) {}

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
        
        auto lambda = [](int v) -> int
        {
            return v;
        };

        auto future = tp.AddTask(lambda, 5);
        auto future2 = tp.AddTask(lambda, 15);
        auto future3 = tp.AddTask(lambda, 25);

    }
    ThreadPool tp;

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

