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
        Firefly() :
            GameObject("")
        {
            decltype(auto) application = Application::GetInstance();
            decltype(auto) engine = application->GetEngine();
            {
                m_timeModule = engine->FindModule<TimeModule>();
            }
            
            m_fireflySpriteComponent = this->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/1536506755.png");
            
            this->Reset();
        }
        
    public:
        virtual void Update() override
        {
            SuperType::Update();
            
            this->Move(Vector3(0.0f, 0.0f, m_speed * m_timeModule->GetTickTime()));
            
//            if ( m_pTexture[0].GetPosition( ).y <= -123.0F )
//                Reset( );
            
           /* if (m_enableOpacityChange)
            {
                float opacity = m_fireflySpriteComponent->GetBlendColor().a;
                
                if (opacity >= 1.0f)
                {
                    needToIncreaseOpacity = false;
                }
                else if (opacity <= 0)
                {
                    needToIncreaseOpacity = true;
                }
                
                if (needToIncreaseOpacity)
                {
                    m_fireflySpriteComponent->GetBlendColor().a += m_opacityChangeSpeed * m_timeModule->GetTickTime();
                }
                else
                {
                     m_fireflySpriteComponent->GetBlendColor().a -= m_opacityChangeSpeed * m_timeModule->GetTickTime();
                }
            }*/
        }
        
    private:
        void Reset()
        {
            m_fireflySpriteComponent->SetBlendColor({1.0f, 1.0f, 1.0f, RandRange(0.4f, 1.0f)});
            
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
    
public:
    IntroScene() :
        m_fadeInObject(std::make_shared<GameObject>("fadeIn")),
        m_cameraObject(std::make_shared<GameObject>("camera1"))
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();
        
        {
            m_graphicsModule = engine->FindModule<GraphicsModule>();
            m_inputModule = engine->FindModule<InputModule>();
            m_timeModule = engine->FindModule<TimeModule>();
        }
        
        {
            const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
            m_cameraObject->AddComponent<CameraComponent>(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f);
        }
        
        for (int i = 0; i < 25; ++i)
        {
            this->AddObject(std::make_shared<Firefly>());
        }
        
        // Intro에 사용할 Sprite 생성
        {
            m_fadeInSpriteComponent = m_fadeInObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_fadeInSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f, 0.4f});
            m_fadeInObject->GetTransform().SetPosition({0.0f, 0.0f});
        }
        this->AddObject(m_fadeInObject);

        SuperType::Update();
    }
    
public:
    virtual void Update() override
    {
        SuperType::Update();
        
//        if (m_fadeInSpriteComponent->GetBlendColor().a >= 0.0f)
//        {
//            m_fadeInSpriteComponent->GetBlendColor().a -= 2.5f * m_timeModule->GetTickTime();
//        }
    }
    
private:
    std::shared_ptr<GraphicsModule> m_graphicsModule;
    std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
    
    std::shared_ptr<GameObject> m_fadeInObject;
    std::shared_ptr<GameObject> m_cameraObject;
    std::shared_ptr<SpriteRendererComponent> m_fadeInSpriteComponent;
};

class TGON_API LogoScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(LogoScene);

public:
    LogoScene() :
        m_cameraObject(std::make_shared<GameObject>("camera1")),
        m_introObject1(std::make_shared<GameObject>("introSprite1")),
        m_introObject2(std::make_shared<GameObject>("introSprite2")),
        m_fadeOutObject(std::make_shared<GameObject>("fadeOut"))
    {
        decltype(auto) application = Application::GetInstance();
        decltype(auto) engine = application->GetEngine();

        {
            m_graphicsModule = engine->FindModule<GraphicsModule>();
            m_inputModule = engine->FindModule<InputModule>();
            m_timeModule = engine->FindModule<TimeModule>();
            m_gameSceneModule = engine->FindModule<GameSceneModule>();
        }
        
        // 카메라 생성
        {
            const I32Extent2D rootWindowSize = application->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
//            m_cameraObject->AddComponent(new CameraComponent(tgon::Rect{ -halfWidth, halfWidth, -halfHeight, halfHeight }, -1024.0f, 1024.0f));
            m_cameraObject->AddComponent<CameraComponent>(Vector3(0.0f, 0.0f, 50.0f), Vector3(0.0f, 0.0f, 0.0f), Pi / 8, 0.1f, 1000.0f);
        }
        this->AddObject(m_cameraObject);

        // Intro에 사용할 Sprite 생성
        {
            m_introSpriteComponent1 = m_introObject1->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
            m_introSpriteComponent1->SetBlendColor({1.0f, 1.0f, 1.0f, 0.0f});
//            m_introObject1->GetTransform().SetScale({8.38f, 4.42f, 1.0f});
        }
        this->AddObject(m_introObject1);

        // Intro에 사용할 Sprite 생성
        {
            m_introSpriteComponent2 = m_introObject2->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_introSpriteComponent2->SetBlendColor({1.0f, 1.0f, 1.0f, 0.0f});
//            m_introObject2->GetTransform().SetScale({8.38f, 4.42f, 1.0f});
        }
        this->AddObject(m_introObject2);
        
        // Intro에 사용할 Sprite 생성
        {
            m_fadeOutSpriteComponent = m_fadeOutObject->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png");
            m_fadeOutSpriteComponent->SetBlendColor({0.0f, 0.0f, 0.0f, 0.0f});
//            m_fadeOutObject->GetTransform().SetScale({8.38f, 4.42f, 1.0f});
        }
        this->AddObject(m_fadeOutObject);
        
        m_beginTime = tgon::GetTickCount();
     
        SuperType::Update();
    }
    
    virtual void Update() override
    {
        SuperType::Update();

        this->OnHandleInput();
        
//        auto elapsedTime = tgon::GetTickCount() - m_beginTime;
//        if (elapsedTime >= 9000)
//        {
//            m_gameSceneModule->ChangeScene<IntroScene>();
//            return;
//        }
//        else if (elapsedTime >= 8000)
//        {
//            if (m_fadeOutSpriteComponent->GetBlendColor().a <= 1.0f)
//            {
//                m_fadeOutSpriteComponent->GetBlendColor().a += 2.5f * m_timeModule->GetTickTime();
//            }
//        }
//        else if (elapsedTime >= 5500)
//        {
//            if (m_introSpriteComponent2->GetBlendColor().a <= 1.0f)
//            {
//                m_introSpriteComponent2->GetBlendColor().a += 1.7f * m_timeModule->GetTickTime();
//            }
//        }
//        else if (elapsedTime >= 4000)
//        {
//            if (m_introSpriteComponent1->GetBlendColor().a >= 0.0f)
//            {
//                m_introSpriteComponent1->GetBlendColor().a -= 1.7f * m_timeModule->GetTickTime();
//            }
//        }
    }
    
    void OnHandleInput()
    {
        static float z = 2.0f;
        decltype(auto) keyboard = m_inputModule->GetKeyboard();
        if (keyboard->IsKeyHold(KeyCode::W))
        {
            z -= 0.01f;
            
            auto& camera = m_cameraObject->GetComponent<CameraComponent>()->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, z});
        }
        if (keyboard->IsKeyHold(KeyCode::S))
        {
            z += 0.01f;
            
            auto& camera = m_cameraObject->GetComponent<CameraComponent>()->GetCamera();
            camera->SetEyePt({0.0f, 0.0f, z});
        }
        if (keyboard->IsKeyDown(KeyCode::Space) || keyboard->IsKeyDown(KeyCode::Return))
        {
            if (tgon::GetTickCount() - m_beginTime <= 5000)
            {
                m_beginTime = tgon::GetTickCount() - 5000;
            }
            else if (tgon::GetTickCount() - m_beginTime <= 9500)
            {
                m_beginTime = tgon::GetTickCount() - 9500;
            }
        }
    }

private:
    int64_t m_beginTime;
    std::shared_ptr<GameObject> m_cameraObject;
    std::shared_ptr<GameObject> m_introObject1;
    std::shared_ptr<GameObject> m_introObject2;
    std::shared_ptr<GameObject> m_fadeOutObject;
    std::shared_ptr<SpriteRendererComponent> m_introSpriteComponent1;
    std::shared_ptr<SpriteRendererComponent> m_introSpriteComponent2;
    std::shared_ptr<SpriteRendererComponent> m_fadeOutSpriteComponent;
    std::shared_ptr<GraphicsModule> m_graphicsModule;
    std::shared_ptr<InputModule> m_inputModule;
    std::shared_ptr<TimeModule> m_timeModule;
    std::weak_ptr<GameSceneModule> m_gameSceneModule;
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

