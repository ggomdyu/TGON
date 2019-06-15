#include "PrecompiledHeader.h"

#include "TGON.h"
#include "ThousandParty.h"
#include "Drawing/FontFactory.h"
#include "String/Encoding.h"
#include "String/UnicodeScalar.h"
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

    auto c1 = UTF8::GetCharCount(u8"가");
    auto c2 = UTF8::GetCharCount(u8"가나다");
    auto c3 = UTF8::GetCharCount(u8"abc");
    auto c4 = UTF8::GetCharCount(u8"가ab");

    FontFactory ff;
    std::shared_ptr<Font> font = ff.GetFont("E:/Users/ggomdyu/Desktop/maplestory.ttf");
    
    char str[] = u8"가";
    char32_t ch = u'가';
    constexpr UnicodeScalar us(u8"가");
    //char32_t c = (str[0] << 0);
    auto& glyphData = font->GetGlyphData(44032, 50);

    for (int y = 0; y < glyphData.size.height; ++y)
        for (int x = 0; x < glyphData.size.width; ++x)
        {
            HWND wndHandle = reinterpret_cast<HWND>(Application::GetInstance()->GetRootWindow()->GetNativeWindow());
            HDC dcHandle = ::GetDC(wndHandle);
            {
                auto color = 255 - glyphData.bitmap[y * glyphData.size.width + x];
                if (color != 255)
                {
                    SetPixel(dcHandle, static_cast<int>(x), static_cast<int>(y), RGB(color, color, color));
                }
            }
            ::ReleaseDC(wndHandle, dcHandle);
        }


    // Input Module
    const auto& rootWindow = Application::GetInstance()->GetRootWindow();
    InputMode inputMode;
    {
        inputMode.isUseMouse = false;
        inputMode.isUseKeyboard = true;
        inputMode.isUseGamepad = false;
    }
    this->RegisterModule<InputModule>(*rootWindow, inputMode);

    //// Graphics Module
    //VideoMode videoMode;
    //{
    //    videoMode.clearColor = Color4f(0.0f, 0.44313f, 0.75686f, 1.0f);
    //    videoMode.enableHardwareAccelerate = true;
    //    videoMode.enableTripleBuffer = false;
    //    videoMode.enableVerticalSync = false;
    //    videoMode.enableMultiSampling = false;
    //};
    //this->RegisterModule<GraphicsModule>(*rootWindow, videoMode);
    
    // Etc
    this->RegisterModule<TimeModule>();
    //this->RegisterModule<TaskModule>();
    //this->RegisterModule<SceneModule>()->ChangeScene(new LogoScene);
}
