#include "PrecompiledHeader.h"

#include "TGON.h"

using namespace tgon;

class TGON_API IntroGameScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(IntroGameScene);

public:
    IntroGameScene()
    {
        using tgon::Rect;
        
        auto camera = std::make_shared<GameObject>("camera1");
        {
            auto rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;

            camera->AddComponent<CameraComponent>(Rect{-halfWidth, halfWidth, -halfHeight, halfHeight}, -1.0f, 1024.0f);
        }
        this->AddObject(camera);

        auto sprite = std::make_shared<GameObject>("sprite1");
        {
            sprite->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/f47d1590fe3a8874fc5ea8f3a76fb5df.png");
            sprite->GetTransform().SetScale({5.f, 6.32f, 1.0f});
        }

        this->AddObject(sprite);
        s.Start();
    }
    Stopwatch s;
    virtual void Update() override
    {
        SuperType::Update();

        if (s.GetElapsedSeconds() > 3)
        {
            Application::GetInstance()->GetRootWindow().SetSize(1200, 600);
            s.Stop();
        }
    }
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
        this->AddModule<InputModule>(inputMode, rootWindow);
        
        VideoMode videoMode;
        {
            videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableTripleBuffer = false;
            videoMode.enableVerticalSync = false;
            videoMode.enableMultiSampling = false;
        };
        this->AddModule<GraphicsModule>(rootWindow, videoMode);
        this->AddModule<GameSceneModule>(std::make_unique<IntroGameScene>());
        this->AddModule<TimeModule>();
    }

/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

