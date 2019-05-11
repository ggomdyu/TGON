#include "PrecompiledHeader.h"

#include "TGON.h"
#include "ThousandParty.h"
#include "LogoScene.h"

TGON_DECLARE_ENGINE(ThousandParty);

using namespace tgon;

void ThousandParty::OnLaunch()
{
    SuperType::OnLaunch();

    this->Initialize();
}

void ThousandParty::OnTerminate()
{
    SuperType::OnTerminate();
}

void ThousandParty::Update()
{
    SuperType::Update();
}

void ThousandParty::Initialize()
{
    this->InitializeModule();
}

void ThousandParty::InitializeModule()
{
    using namespace tgon;
    
    const auto& rootWindow = Application::GetInstance()->GetRootWindow();
    InputMode inputMode;
    {
        inputMode.isUseMouse = false;
        inputMode.isUseKeyboard = true;
        inputMode.isUseGamepad = false;
    }
    this->RegisterModule<InputModule>(rootWindow, inputMode);

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
