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
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
        
//        constexpr float a = Floor(4.0f);
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance().GetRootWindow());
        
        this->AddModule<TimeModule>();
        
        this->AddModule<SceneModule>(std::make_unique<TestScene>(), Application::GetInstance().GetRootWindow(), VideoMode{});
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

