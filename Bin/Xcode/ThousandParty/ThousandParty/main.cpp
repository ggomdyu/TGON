#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);
    
/* @section Public constructor */
public:
    ThousandParty() = default;

/* @section Public destructor */
public:
    virtual ~ThousandParty() = default;

/* @section Public event handler */
public:
    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
        
        this->AddModule<TimeModule>();
        this->AddModule<EventModule>();
        this->AddModule<GraphicsModule>(VideoMode{}, Application::GetInstance()->GetRootWindow());
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
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
    
    virtual WindowStyle GetRootWindowStyle() const noexcept override
    {
        WindowStyle windowStyle;
        windowStyle.title = "Thousand Party";
        
        return windowStyle;
    }
    
/* @section Private variable */
private:
    Delegate<void()> m_onGoldGain;
};

TGON_DECLARE_ENGINE(ThousandParty);
