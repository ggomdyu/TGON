#include "PrecompiledHeader.h"

#include "TGON.h"
#include "ThousandParty.h"
#include "LogoScene.h"

#include <StackWalker-1.20\Main\StackWalker\StackWalker.h>

TGON_DECLARE_ENGINE(ThousandParty);

void ThousandParty::OnDidLaunch()
{
    SuperType::OnDidLaunch();

    tgon::Sprite s(tgon::GetDesktopDirectory() + "/Assets/Image/IntroScene/girl.png");

    this->Initialize();
}

void ThousandParty::OnWillTerminate()
{
    SuperType::OnWillTerminate();
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
    tgon::Application::GetInstance()->EnableCrashHandler();

    tgon::Window& rootWindow = tgon::Application::GetInstance()->GetRootWindow();
    tgon::InputMode inputMode;
    {
        inputMode.isUseMouse = false;
        inputMode.isUseKeyboard = true;
        inputMode.isUseGamepad = false;
    }
    this->RegisterModule<tgon::InputModule>(inputMode, rootWindow);

    tgon::VideoMode videoMode;
    {
        videoMode.clearColor = tgon::Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
        videoMode.enableHardwareAccelerate = true;
        videoMode.enableTripleBuffer = false;
        videoMode.enableVerticalSync = false;
        videoMode.enableMultiSampling = false;
    };
    this->RegisterModule<tgon::GraphicsModule>(rootWindow, videoMode);
    this->RegisterModule<tgon::TimeModule>();
    this->RegisterModule<tgon::GameSceneModule>()->ChangeScene<LogoScene>();
}
