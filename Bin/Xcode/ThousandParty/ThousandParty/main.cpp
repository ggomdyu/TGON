#include "PrecompiledHeader.h"

#include "TGON.h"

#include "Core/Utility/NonAddressable.h"

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
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = true;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
        this->AddModule<TimeModule>();
        this->AddModule<SceneManagementModule>(VideoMode{}, Application::GetInstance()->GetRootWindow());
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
