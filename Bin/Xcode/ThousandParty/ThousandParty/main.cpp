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
        
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
        this->AddModule<GraphicsModule>(VideoMode{}, Application::GetInstance()->GetRootWindow());
        this->AddModule<TimeModule>();
        
        GameObject gameObject("sprite");
        gameObject.AddComponent(std::make_unique<SpriteComponent>(&gameObject));
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
    
/* @section Private variable */
private:
};

TGON_DECLARE_ENGINE(ThousandParty);
