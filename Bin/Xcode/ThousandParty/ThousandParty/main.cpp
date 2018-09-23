#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API IntroScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(IntroScene);
    
private:
    class TGON_API Firefly final :
        public GameObject
    {
    public:
        TGON_RUNTIME_OBJECT(Firefly);
        
    public:
        Firefly(const FixedHashString32& name) :
            GameObject(name)
        {
            decltype(auto) application = Application::GetInstance();
            decltype(auto) engine = application->GetEngine();
            
            m_timeModule = engine->FindModule<TimeModule>();
            
            m_fireflySpriteComponent = this->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "Assets/Image/IntroScene/firefly.png");
            m_fireflySpriteComponent->SetBlendColor({1.0f, 1.0f, 1.0f});
            
            this->SetScale({0.31f, 0.31f, 1.0f});
            
            this->Reset();
        }
        
    public:
        virtual void Update() override
        {
            SuperType::Update();
            
            this->Move(Vector3(0.0f, 0.0f, m_speed * m_timeModule->GetTickTime()));
            
//            if ( m_pTexture[0].GetPosition( ).y <= -123.0F )
//                Reset( );
            
            if (m_enableOpacityChange)
            {
//                float opacity = m_fireflySpriteComponent->GetBlendColor().a;
                
//                if (opacity >= 1.0f)
//                {
//                    needToIncreaseOpacity = false;
//                }
//                else if (opacity <= 0)
//                {
//                    needToIncreaseOpacity = true;
//                }
                
//                if (needToIncreaseOpacity)
//                {
//                    m_fireflySpriteComponent->GetBlendColor().a += m_opacityChangeSpeed * m_timeModule->GetTickTime();
//                }
//                else
//                {
//                     m_fireflySpriteComponent->GetBlendColor().a -= m_opacityChangeSpeed * m_timeModule->GetTickTime();
//                }
            }
        }
        
    private:
        void Reset()
        {
            m_fireflySpriteComponent->SetBlendColor({1.0f, 1.0f, 1.0f});
            
            this->SetScale({0.1f, 0.1f, 1.0f});
            
//            I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            this->SetPosition({RandRange(-0.5f, 0.5f), 0.0f, -3.0f});
//            RandRange(-rootWindowSize.width * 0.5f, rootWindowSize.width * 0.5f)
//            -rootWindowSize.height * 0.5f
            m_enableOpacityChange = ( RandRange(0, 2) == 0 ) ? true : false;
            m_opacityChangeSpeed = RandRange(0.00392f, 0.01568f);
            m_speed = RandRange(0.3f, 1.0f);
        }
        
    private:
        bool m_enableOpacityChange = false;
        bool needToIncreaseOpacity = false;
        float m_opacityChangeSpeed = 0.0f;
        float m_speed = 0.0f;
        std::shared_ptr<SpriteRendererComponent> m_fireflySpriteComponent;
        std::shared_ptr<TimeModule> m_timeModule;
    };
    float camZ;
public:
    IntroScene()
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();
        
        auto rootWindowSize = application->GetRootWindow().GetSize();
        
        m_graphicsModule = engine->FindModule<GraphicsModule>();
        m_inputModule = engine->FindModule<InputModule>();
        m_timeModule = engine->FindModule<TimeModule>();
        
        m_graphicsModule->GetGraphics().DisableDepthTest();
        m_graphicsModule->GetGraphics().EnableBlend();
        m_graphicsModule->GetGraphics().SetBlendMode(BlendMode::Alpha);
        
        // 카메라 생성
        {
            auto cameraObject = std::make_shared<GameObject>("camera1");
            const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
            camZ = 50.0f;
//            m_cameraComponent = cameraObject->AddComponent<CameraComponent>(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
            this->AddObject(cameraObject);
        }
        
//        for (int i = 0; i < 25; ++i)
//        {
//            this->AddObject(std::make_shared<Firefly>(StringTraits<char>::Format("firefly_%d", i).first));
//        }
        
        // Intro에 사용할 Sprite 생성
        {
            auto fadeInObject = std::make_shared<GameObject>("fadeIn");
            fadeInObject->SetScale({8.38f, 4.42f, 1.0f});
            fadeInObject->SetPosition({0.0f, 0.0f, 10.0f});
            m_fadeInSpriteComponent = fadeInObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_fadeInSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f});
            m_fadeInSpriteComponent->SetOpacity(1.0f);
            this->AddObject(fadeInObject);
        }
        
        // Intro에 사용할 Sprite 생성
        {
            m_nightSkyObject = std::make_shared<GameObject>("nightSky");
            m_nightSkySpriteComponent = m_nightSkyObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/IntroScene/nightSky.png");
            float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
            m_nightSkyObject->SetScale({25.14f, 4.42f, 1.0f});
            //m_nightSkyObject->GetTransform().SetPosition({static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01 * 0.5f, 0.0f, 0.0f});
            this->AddObject(m_nightSkyObject);
        }

        SuperType::Update();
    }
    
public:
    virtual void Update() override
    {
        SuperType::Update();
        
        if (m_fadeInSpriteComponent->GetOpacity() >= 0.0f)
        {
            m_fadeInSpriteComponent->GetOpacity() -= 0.025f * m_timeModule->GetTickTime();
        }
        
        decltype(auto) keyboard = m_inputModule->GetKeyboard();
        if (keyboard->IsKeyHold(KeyCode::W))
        {
            camZ -= 0.05f;
            
            auto& camera = m_cameraComponent->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, camZ});
        }
        if (keyboard->IsKeyHold(KeyCode::S))
        {
            camZ += 0.05f;
            
            auto& camera = m_cameraComponent->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, camZ});
        }
        
        if (keyboard->IsKeyHold(KeyCode::Q))
        {
            m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, -0.05f});
        }
        if (keyboard->IsKeyHold(KeyCode::A))
        {
            m_fadeInSpriteComponent->GetOwner()->Move({0.0f, 0.0f, 0.05f});
        }
        
        // Move NightSky
        {
            auto rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            float nightSkyImageWidth = static_cast<float>(m_nightSkySpriteComponent->GetSprite().GetTexture()->GetWidth());
            float nightSkyImageLeftTopX = static_cast<float>(nightSkyImageWidth - rootWindowSize.width) * 0.01f * 0.5f;
            if (m_nightSkyObject->GetPosition().x <= -nightSkyImageLeftTopX)
            {
                m_nightSkyObject->SetPosition({nightSkyImageLeftTopX, 0.0f, 0.0f});
            }
            else
            {
                m_nightSkyObject->Move({-1.0f * m_timeModule->GetTickTime(), 0.0f, 0.0f});
            }
        }
    }
    
private:
    std::shared_ptr<GraphicsModule> m_graphicsModule;
    std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
    
    std::shared_ptr<GameObject> m_nightSkyObject;
    
    std::shared_ptr<CameraComponent> m_cameraComponent;
    std::shared_ptr<SpriteRendererComponent> m_fadeInSpriteComponent;
    std::shared_ptr<SpriteRendererComponent> m_nightSkySpriteComponent;
};

class TGON_API LogoScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(LogoScene);

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

        // Intro에 사용할 Sprite 생성
        {
            auto introObject1 = std::make_shared<GameObject>("introSprite1");
            introObject1->SetScale({8.38f, 4.42f, 1.0f});
            m_introSpriteComponent1 = introObject1->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_introSpriteComponent1->SetBlendColor({1.0f, 1.0f, 1.0f});
            m_introSpriteComponent1->SetOpacity(0.0f);
            this->AddObject(introObject1);
        }

        // Intro에 사용할 Sprite 생성
        {
            auto introObject2 = std::make_shared<GameObject>("introSprite2");
            introObject2->SetScale({8.38f, 4.42f, 1.0f});
            m_introSpriteComponent2 = introObject2->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
            m_introSpriteComponent2->SetBlendColor({1.0f, 1.0f, 1.0f});
            m_introSpriteComponent2->SetOpacity(0.0f);
            this->AddObject(introObject2);
        }
        
        // Intro에 사용할 Sprite 생성
        {
            auto fadeOutObject = std::make_shared<GameObject>("fadeOut");
            fadeOutObject->SetScale({8.38f, 4.42f, 1.0f});
            m_fadeOutSpriteComponent = fadeOutObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_fadeOutSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f});
            m_fadeOutSpriteComponent->SetOpacity(0.0f);
            this->AddObject(fadeOutObject);
        }
        
        m_beginTime = tgon::GetTickCount();
     
        SuperType::Update();
    }
    
    virtual void Update() override
    {
        SuperType::Update();

        this->OnHandleInput();

        auto elapsedTime = tgon::GetTickCount() - m_beginTime;
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
        }
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
    TGON_RUNTIME_OBJECT(ThousandParty);

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

