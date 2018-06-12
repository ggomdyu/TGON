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
            inputMode.isUseMouse = true;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = true;
        }
        this->AddModule<InputModule>(inputMode, Application::GetInstance()->GetRootWindow());
        this->AddModule<GraphicsModule>(VideoMode{}, Application::GetInstance()->GetRootWindow());
        this->AddModule<TimeModule>();
        
        GameObject gameObject("sprite");
        gameObject.AddComponent(std::make_unique<SpriteComponent>("z"));
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

        auto& keyboard = GetModule<InputModule>()->GetKeyboard();
        if (keyboard->IsKeyDown(KeyCode::Space))
        {
            Log(LogLevel::Debug, "Down\n");
        }
        else if (keyboard->IsKeyHold(KeyCode::Space))
        {
            Log(LogLevel::Debug, "Hold\n");
        }
        else if (keyboard->IsKeyUp(KeyCode::Space))
        {
            Log(LogLevel::Debug, "Up\n");
        }

        auto& mouse = GetModule<InputModule>()->GetMouse();
        if (mouse->IsMouseDown(MouseCode::Left))
        {
            Log(LogLevel::Debug, "Down\n");
        }
        else if (mouse->IsMouseHold(MouseCode::Left))
        {
            Log(LogLevel::Debug, "Hold\n");
        }
        else if (mouse->IsMouseUp(MouseCode::Left))
        {
            Log(LogLevel::Debug, "Up\n");
        }
    }
    
/* @section Private variable */
private:
};

TGON_DECLARE_ENGINE(ThousandParty);
