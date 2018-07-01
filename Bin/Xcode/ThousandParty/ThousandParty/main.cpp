#include "PrecompiledHeader.h"

#include "TGON.h"
#include "TestScene.h"

#include "Core/Object/DelegateChain.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public event handler */
public:
    ThousandParty() :
        m_audioBuffer(std::make_shared<AudioBuffer>(GetDesktopDirectory() + "/Sulk.ogg")),
        m_audioPlayer(m_audioBuffer)
    {
        m_audioPlayer.SetPitch(1.2f);
        m_audioPlayer.Play();
        
        Delegate<void()> d1 = []() { Log(LogLevel::Debug, "1"); };
        Delegate<void()> t(std::move(d1));
        
        Delegate<void()> d2 = []() { Log(LogLevel::Debug, "2"); };
        Delegate<void()> d3 = []() { Log(LogLevel::Debug, "3"); };
        DelegateChain<void()> dc{ d1, d2, d3 };
        dc.Invoke();
    }

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
        
        this->AddModule<SceneModule>(std::make_unique<TestScene>(), VideoMode{}, Application::GetInstance()->GetRootWindow());   
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
    
private:
    std::shared_ptr<AudioBuffer> m_audioBuffer;
    AudioPlayer m_audioPlayer;
};

TGON_DECLARE_ENGINE(ThousandParty);

