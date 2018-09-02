#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API IntroGameScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(IntroGameScene);

public:
    IntroGameScene() :
        m_cameraObject(std::make_shared<GameObject>("camera1")),
        m_introSpriteObject1(std::make_shared<GameObject>("introSprite1")),
        m_introSpriteObject2(std::make_shared<GameObject>("introSprite2"))
    {
        // 카메라 생성
        {
            const I32Extent2D rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            const float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            const float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;
            m_cameraObject->AddComponent(new CameraComponent(tgon::Rect{-halfWidth, halfWidth, -halfHeight, halfHeight}, -1.0f, 1024.0f));
        }
        this->AddObject(m_cameraObject);

        // Intro에 사용할 Sprite 생성
        {
            auto spriteRendererComponent = new SpriteRendererComponent(GetDesktopDirectory() + "/Assets/Image/LogoScene/onLogo.png");
            spriteRendererComponent->SetBlendColor({1.0f, 1.0f, 1.0f, 0.5f});
            m_introSpriteObject1->AddComponent(spriteRendererComponent);
        }
        this->AddObject(m_introSpriteObject1);

        // Intro에 사용할 Sprite 생성
        {
            //m_introSpriteObject2->AddComponent(new SpriteRendererComponent(GetDesktopDirectory() + "/Assets/Image/LogoScene/teamTPLogo.png"));
        }
        //this->AddObject(m_introSpriteObject2);
    }

    virtual void Update() override
    {
        SuperType::Update();

        
    }

private:
    Stopwatch m_stopwatch;
    std::shared_ptr<GameObject> m_cameraObject;
    std::shared_ptr<GameObject> m_introSpriteObject1;
    std::shared_ptr<GameObject> m_introSpriteObject2;
};

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public constructor */
public:
    ThousandParty() {}

/* @section Public destructor */
public:
    virtual ~ThousandParty() override {}

/* @section Public event handler */
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
        this->RegisterModule(new InputModule(inputMode, rootWindow));
        
        VideoMode videoMode;
        {
            videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableTripleBuffer = false;
            videoMode.enableVerticalSync = false;
            videoMode.enableMultiSampling = false;
        };
        this->RegisterModule(new GraphicsModule(rootWindow, videoMode));
        this->RegisterModule(new GameSceneModule(std::make_unique<IntroGameScene>()));
        this->RegisterModule(new TimeModule());
    }

/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

