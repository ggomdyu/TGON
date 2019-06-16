#include "PrecompiledHeader.h"

#include "TGON.h"
#include "ThousandParty.h"
#include "Drawing/FontFactory.h"
#include "String/Encoding.h"
#include "String/UnicodeScalar.h"
#include "LogoScene.h"
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>

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
    
    char a[16] {};
    int n = UTF16LE::ConvertTo<UTF8>(std::wstring_view(L"가가가e"), a);

    wchar_t b[16] {};
    int c = UTF8::ConvertTo<UTF16LE>(std::string_view(a, strlen(a)), b);

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
