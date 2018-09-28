#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API LogoScene :
    public GameScene
{
public:
    TGON_DECLARE_RTTI(LogoScene);

public:
    LogoScene()
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();

        m_graphicsModule = engine->FindModule<GraphicsModule>();
        m_inputModule = engine->FindModule<InputModule>();
        m_timeModule = engine->FindModule<TimeModule>();
        
        m_graphicsModule->GetGraphics().DisableDepthTest();
        m_graphicsModule->GetGraphics().SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});

        // 카메라 생성
        {
            auto cameraObject = std::make_shared<GameObject>("camera1");
            const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
            //m_cameraComponent = cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
            this->AddObject(cameraObject);
        }

        //// Intro에 사용할 Sprite 생성
        //{
        //    auto introObject1 = std::make_shared<GameObject>("introSprite1");
        //    introObject1->SetScale({8.38f, 4.42f, 1.0f});
        //    m_introSpriteComponent1 = introObject1->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
        //    m_introSpriteComponent1->SetBlendColor({1.0f, 1.0f, 1.0f});
        //    m_introSpriteComponent1->SetOpacity(0.0f);
        //    this->AddObject(introObject1);
        //}

        //// Intro에 사용할 Sprite 생성
        //{
        //    auto introObject2 = std::make_shared<GameObject>("introSprite2");
        //    introObject2->SetScale({8.38f, 4.42f, 1.0f});
        //    m_introSpriteComponent2 = introObject2->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
        //    m_introSpriteComponent2->SetBlendColor({1.0f, 1.0f, 1.0f});
        //    m_introSpriteComponent2->SetOpacity(0.0f);
        //    this->AddObject(introObject2);
        //}
        //
        //// Intro에 사용할 Sprite 생성
        //{
        //    auto fadeOutObject = std::make_shared<GameObject>("fadeOut");
        //    fadeOutObject->SetScale({8.38f, 4.42f, 1.0f});
        //    m_fadeOutSpriteComponent = fadeOutObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
        //    m_fadeOutSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f});
        //    m_fadeOutSpriteComponent->SetOpacity(0.0f);
        //    this->AddObject(fadeOutObject);
        //}
        //
        m_beginTime = tgon::GetTickCount();
     
        SuperType::Update();
    }
    
    virtual void Update() override
    {
        SuperType::Update();

        this->OnHandleInput();

      /*  auto elapsedTime = tgon::GetTickCount() - m_beginTime;
        if (elapsedTime >= 8500)
        {
            auto gameSceneModule = Application::GetInstance()->GetEngine()->FindModule<GameSceneModule>();

            gameSceneModule->ChangeScene<IntroScene>();
            return;
        }
        else if (elapsedTime >= 7500)
        {
            if (m_fadeOutSpriteComponent->GetOpacity() <= 1.0f)
            {
                m_fadeOutSpriteComponent->GetOpacity() += 2.5f * m_timeModule->GetTickTime();
            }
        }
        else if (elapsedTime >= 5000)
        {
            if (m_introSpriteComponent2->GetOpacity() <= 1.0f)
            {
                m_introSpriteComponent2->GetOpacity() += 2.0f * m_timeModule->GetTickTime();
            }
        }
        else if (elapsedTime >= 3500)
        {
            if (m_introSpriteComponent1->GetOpacity() >= 0.0f)
            {
                m_introSpriteComponent1->GetOpacity() -= 2.0f * m_timeModule->GetTickTime();
            }
        }
        else if (elapsedTime >= 1000)
        {
            if (m_introSpriteComponent1->GetOpacity() <= 1.0f)
            {
                m_introSpriteComponent1->GetOpacity() += 2.0f * m_timeModule->GetTickTime();
            }
        }*/
    }
    
    void OnHandleInput()
    {
        decltype(auto) keyboard = m_inputModule->GetKeyboard();
        if (keyboard->IsKeyDown(KeyCode::Space) || keyboard->IsKeyDown(KeyCode::Return))
        {
            auto currTime = tgon::GetTickCount();
            auto elapsedTime = currTime - m_beginTime;
            if (elapsedTime <= 1000)
            {
                m_beginTime = currTime - 1000.0f;
            }
            else if (elapsedTime <= 3500)
            {
                m_beginTime = currTime - 3500.0f;
            }
            else if (elapsedTime <= 5000)
            {
                m_beginTime = currTime - 5000.0f;
            }
            else if (elapsedTime <= 7500)
            {
                m_beginTime = currTime - 7500.0f;
            }
        }
    }

private:
    int64_t m_beginTime;
    std::shared_ptr<CameraComponent> m_cameraComponent;
    std::shared_ptr<SpriteRendererComponent> m_introSpriteComponent1;
    std::shared_ptr<SpriteRendererComponent> m_introSpriteComponent2;
    std::shared_ptr<SpriteRendererComponent> m_fadeOutSpriteComponent;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
    std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
};

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_DECLARE_RTTI(ThousandParty);

/**@section Public constructor */
public:
    ThousandParty() {}

/**@section Public destructor */
public:
    virtual ~ThousandParty() override {}

/**@section Public event handler */
public:
    virtual void OnDidLaunch() override
    {
        Window& rootWindow = Application::GetInstance()->GetRootWindow();
        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        this->RegisterModule<InputModule>(inputMode, rootWindow);
        
        VideoMode videoMode;
        {
            videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableTripleBuffer = false;
            videoMode.enableVerticalSync = false;
            videoMode.enableMultiSampling = false;
        };
        this->RegisterModule<GraphicsModule>(rootWindow, videoMode);
        this->RegisterModule<TimeModule>();
        this->RegisterModule<GameSceneModule>()->ChangeScene<LogoScene>();
        
    }

/**@section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

