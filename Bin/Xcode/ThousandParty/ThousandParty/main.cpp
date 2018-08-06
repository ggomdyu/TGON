#include "PrecompiledHeader.h"

#include "TGON.h"
#include "TestScene.h"

using namespace tgon;

class TGON_API ThousandParty final :
    public Engine
{
public:
    TGON_RUNTIME_OBJECT(ThousandParty);

/* @section Public constructor */
public:
    ThousandParty()
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
            videoMode.graphicsSDK = GraphicsSDK::OpenGL4_0;
            videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
            videoMode.enableHardwareAccelerate = true;
            videoMode.enableTripleBuffer = false;
            videoMode.enableVerticalSync = false;
            videoMode.enableMultiSampling = false;
        };
        this->AddModule<GraphicsModule>(rootWindow, videoMode);

        this->AddModule<AudioModule>();

        this->AddModule<TimeModule>();

        this->AddModule<ResourceModule>()->Load();
    }

/* @section Public destructor */
public:
    virtual ~ThousandParty() override
    {
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

