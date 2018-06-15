#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public event handler */
public:
    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
        
        StringViewHash svh = "WOW";
        svh[0] = 'a';

        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule(new InputModule(inputMode, Application::GetInstance()->GetRootWindow()));
        this->AddModule(new GraphicsModule(VideoMode{}, Application::GetInstance()->GetRootWindow()));
        this->AddModule(new TimeModule);

        m_weakInputModule = GetModule<InputModule>();
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

        auto inputModule = m_weakInputModule.lock();
        if (inputModule != nullptr)
        {
            auto& keyboard = inputModule->GetKeyboard();
            if (keyboard->IsKeyUp(KeyCode::Space))
            {
                Log(LogLevel::Debug, "HI!");
            }
        }
    }
    
/* @section Private variable */
private:
    std::weak_ptr<InputModule> m_weakInputModule;
};

TGON_DECLARE_ENGINE(ThousandParty);
