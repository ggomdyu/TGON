#include "PrecompiledHeader.h"

#include "TGON.h"

#include "Graphics/Render/GraphicsResource.h"
#include "Graphics/Render/SpriteBatch.h"
#include "Core/Debug/Log.h"

class A
{
public:
    virtual void foo()
    {
        tgon::Log(tgon::LogLevel::Debug, "WOW!");
    }
};

class B :
    public A
{
public:
    virtual void foo() override
    {
        tgon::Log(tgon::LogLevel::Debug, "WOW2!");
    }
};

using namespace tgon;

class TGON_API ThousandParty final :
    public Application
{
public:
    ThousandParty() :
        Application(WindowStyle())
    {
        this->AddModule<TimeModule>();
        this->AddModule<EventModule>();
        this->AddModule<GraphicsModule>(VideoMode(), this->GetRootWindow());

       /* InputMode inputMode;
        {
            inputMode.isUseKeyboard = true;
            inputMode.isUseMouse = false;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, this->GetRootWindow());*/
    }

    SpriteBatch m_spriteBatch;
    GraphicsContext* m_graphicsContext;
    std::vector<std::shared_ptr<Sprite>> m_sprites;

/* @section Public destructor */
public:
    virtual ~ThousandParty()
    {
    }

/* @section Public event handler */
public:
    virtual void OnLaunch() override
    {
        //SuperType::OnWillLaunch();
    }

    virtual void OnUpdate() override
    {
        //SuperType::OnUpdate();
        
        decltype(auto) inputModule = GetModule<InputModule>();
        
        /*decltype(auto) keyboard = inputModule->GetKeyboard();
        if (keyboard->IsKeyDown(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "1");
        }
        else if (keyboard->IsKeyHold(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "2");
        }
        else if (keyboard->IsKeyUp(Keyboard::KeyCode::Space))
        {
            Log(LogLevel::Debug, "3");
        }*/

       /* m_spriteBatch.AddSprite(m_sprites[0]);
        m_spriteBatch.AddSprite(m_sprites[1]);
        m_spriteBatch.AddSprite(m_sprites[2]);*/
        
        auto& graphics = GetModule<GraphicsModule>()->GetGraphics();
        graphics.ClearColorDepthBuffer();
        {
            /* Add batch render */
            m_spriteBatch.FlushBatch(*m_graphicsContext);
        }
        graphics.SwapBuffer();
        
        /*decltype(auto) mouse = inputModule->GetMouse();
        if (mouse->IsMouseDown(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "1");
        }
        else if (mouse->IsMouseHold(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "2");
        }
        else if (mouse->IsMouseUp(Mouse::MouseCode::Left))
        {
            Log(LogLevel::Debug, "3");
        }
*/
        /*decltype(auto) gamepad = inputModule->GetGamepad();
        gamepad->Vibrate(0.0f, 0.0f);*/
    }
};

TGON_DECLARE_APPLICATION(ThousandParty)
