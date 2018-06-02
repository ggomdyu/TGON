#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Application
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty)

public:
    ThousandParty() :
        Application(WindowStyle())
    {
        this->AddModule<TimeModule>();
        this->AddModule<EventModule>();
        this->AddModule<GraphicsModule>(VideoMode(), this->GetRootWindow());
        this->AddModule<InputModule>([]()
        {
            InputMode inputMode;
            inputMode.isUseKeyboard = true;
            inputMode.isUseMouse = true;
            return inputMode;
        } ());
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
    }

/* @section Public event handler */
public:
    virtual void OnWillLaunch() override
    {
        SuperType::OnWillLaunch();
    }

    virtual void OnDidLaunch() override
    {
        SuperType::OnDidLaunch();
    }

    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
        
        decltype(auto) inputModule = GetModule<InputModule>();
        
        decltype(auto) keyboard = inputModule->GetKeyboard();
        if (keyboard->IsKeyDown(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "Space Down");
        }
        else if (keyboard->IsKeyUp(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "Space Up");
        }
        
        decltype(auto) mouse = inputModule->GetMouse();
        if (mouse->IsMouseDown(Mouse::MouseCode::Right))
        {
            Log(LogLevel::Debug, "LeftMouse Down");
        }
        else if (mouse->IsMouseUp(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "LeftMouse Up");
        }
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
