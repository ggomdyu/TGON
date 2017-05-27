#include "PrecompiledHeader.h"

#include "WindowsApplication.h"
#include "WindowsWindow.h"

namespace tgon {
namespace platform {

TGON_API void ShowOkPopup(const char* message, const char* caption, OkPopupEventHandler onMessageBoxEventHandled)
{
    MessageBoxA(nullptr, message, caption, MB_OK);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled();
    }
}

TGON_API void ShowYesNoPopup(const char* message, const char* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxA(nullptr, message, caption, MB_YESNO);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

namespace windows {

TGON_API void ShowYesNoPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxW(nullptr, message, caption, MB_YESNO);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

TGON_API void ShowOkPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxW(nullptr, message, caption, MB_OK);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

TGON_API void EnableFloatException(unsigned int flag)
{
    unsigned int currentFlag;
    _controlfp_s(&currentFlag, 0, 0);

    unsigned int newFlag = currentFlag;
    newFlag &= ~flag;
    _controlfp_s(&currentFlag, newFlag, MCW_EM);
}

TGON_API HINSTANCE GetInstanceHandle()
{
    static HINSTANCE instanceHandle = GetModuleHandle(nullptr);
    return instanceHandle;
}
    
} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */