#include "PrecompiledHeader.h"

#include "TGON.h"

#include "Graphics/Render/GraphicsResource.h"
#include "Graphics/Render/SpriteBatch.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Application
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

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

        
        auto extent = GetRootWindow()->GetSize();
        
        auto matViewProj = Matrix4x4::LookAtRH({ 0.0f, 0.0f, -50.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
        matViewProj *= Matrix4x4::PerspectiveRH(Pi / 8.0f, (float)extent.width / (float)extent.height, 0.1f, 1000.0f);
    
        auto spriteMatWVP  = Matrix4x4::Translate(-4.0f, 0.0f, 0.0f) * matViewProj;
        auto sprite = std::make_shared<Sprite>();
        sprite->SetTexture(std::make_shared<Texture>(GetDesktopDirectory() + "/printTestImage.png"));
        sprite->SetWorldViewProjectionMatrix(spriteMatWVP);
        m_sprites.push_back(sprite);

        spriteMatWVP  = Matrix4x4::Translate(0.0f, 0.0f, 0.0f) * matViewProj;
        sprite = std::make_shared<Sprite>();
        sprite->SetTexture(std::shared_ptr<Texture>(new Texture(GetDesktopDirectory() + "/printTestImage.png")));
        sprite->SetWorldViewProjectionMatrix(spriteMatWVP);
        m_sprites.push_back(sprite);

        spriteMatWVP  = Matrix4x4::Translate(4.0f, 0.0f, 0.0f) * matViewProj;
        sprite = std::make_shared<Sprite>();
        sprite->SetTexture(std::shared_ptr<Texture>(new Texture(GetDesktopDirectory() + "/test.png")));
        sprite->SetWorldViewProjectionMatrix(spriteMatWVP);
        m_sprites.push_back(sprite);


        auto graphicsModule = GetModule<GraphicsModule>();
        m_graphicsContext = new GraphicsContext(graphicsModule->GetGraphics());
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

        m_spriteBatch.AddSprite(m_sprites[0]);
        m_spriteBatch.AddSprite(m_sprites[1]);
        m_spriteBatch.AddSprite(m_sprites[2]);
        
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
