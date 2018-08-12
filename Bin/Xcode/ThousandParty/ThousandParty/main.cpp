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
        auto sprite = std::make_shared<GameObject>("sprite1");
        {
            sprite->AddComponent<SpriteRendererComponent>(GetDesktopDirectory() + "/grass.png");
        }

        this->AddObject(sprite);
    }

    virtual void Update() override
    {
        SuperType::Update();
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

        InputMode inputMode;
        {
            inputMode.isUseMouse = false;
            inputMode.isUseKeyboard = true;
            inputMode.isUseGamepad = false;
        }
        
        VideoMode videoMode;
        {
            videoMode.graphicsSDK = GraphicsSDK::OpenGL4_0;
            videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableTripleBuffer = false;
            videoMode.enableVerticalSync = false;
            videoMode.enableMultiSampling = false;
        };

        this->AddModule<InputModule>(inputMode, rootWindow);
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

