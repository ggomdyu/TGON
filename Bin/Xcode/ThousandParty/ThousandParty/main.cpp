#include "PrecompiledHeader.h"

#include "TGON.h"

#include <glm/glm/matrix.hpp>

using namespace tgon;

class TGON_API IntroGameScene :
    public GameScene
{
public:
    TGON_RUNTIME_OBJECT(IntroGameScene);

public:
    IntroGameScene()
    {
        auto camera = std::make_shared<GameObject>("camera1");
        {
            auto rootWindowSize = Application::GetInstance()->GetRootWindow().GetSize();
            float halfWidth = static_cast<float>(rootWindowSize.width) * 0.5f;
            float halfHeight = static_cast<float>(rootWindowSize.height) * 0.5f;

            camera->AddComponent<CameraComponent>(FRect{-halfWidth, halfWidth, -halfHeight, halfHeight}, -1.0f, 1024.0f);
        }
        this->AddObject(camera);

        auto sprite = std::make_shared<GameObject>("sprite1");
        {
            sprite->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/3243.png");
            sprite->GetTransform().SetScale(Vector3(1178, 763, 1.0f));
            sprite->GetTransform().SetPosition(Vector3(-0.5f, -0.5f, 1.0f));
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
    virtual void OnDidLaunch()
    {
        Window& rootWindow = Application::GetInstance()->GetRootWindow();

        /*InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = false;
            inputMode.isUseGamepad = false;
        }
        this->AddModule<InputModule>(inputMode, rootWindow);*/
        
        VideoMode videoMode;
        {
            videoMode.graphicsSDK = GraphicsSDK::OpenGL4_0;
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
    
/* @section Private method */
private:

/* @section Public method */
public:
    virtual void Update() override
    {
        SuperType::Update();
    }
};

TGON_DECLARE_ENGINE(ThousandParty);

