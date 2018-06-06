#include "PrecompiledHeader.h"

#include "TGON.h"

#include "Graphics/Render/Sprite.h"

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

        InputMode inputMode;
        {
            inputMode.isUseKeyboard = true;
            inputMode.isUseMouse = false;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, this->GetRootWindow());

        m_sprite = new Sprite();
        m_sprite->SetTexture(std::shared_ptr<Texture>(new Texture("E:/Users/ggomdyu/Desktop/printTestImage.png")));

        auto graphicsModule = GetModule<GraphicsModule>();
        m_graphicsContext = new GraphicsContext(graphicsModule->GetGraphics());
    }

    
    GraphicsContext* m_graphicsContext;
    Sprite* m_sprite;

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
        m_stopwatch.Start();
    }

    Stopwatch m_stopwatch;

    virtual void OnUpdate() override
    {
        SuperType::OnUpdate();
        
        decltype(auto) inputModule = GetModule<InputModule>();
        
        decltype(auto) keyboard = inputModule->GetKeyboard();
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
        }

        auto extent = GetRootWindow()->GetSize();
        
        static float zAxis = Pi;
        auto matWorld  = Matrix4x4::Scale(1.0f, 1.0f, 1.0f);
        matWorld *= Matrix4x4::RotateZ(zAxis);;
        auto matView = Matrix4x4::LookAtRH({ 0.0f, 0.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        auto matProj = Matrix4x4::PerspectiveRH(Pi / 8.0f, (float)extent.width / (float)extent.height, 0.1f, 1000.0f);


        Matrix4x4 matWVP = matWorld;
        matWVP *= matView;
        matWVP *= matProj;

        m_sprite->SetWorldViewProjectionMatrix(matWVP);

        auto& graphics = GetModule<GraphicsModule>()->GetGraphics();
        graphics.ClearColorDepthBuffer();
        {
            /* Add batch render */
            m_sprite->Draw(*m_graphicsContext);
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