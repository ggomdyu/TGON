#include "PrecompiledHeader.h"

#include "WindowsApplication.h"
#include "WindowsWindow.h"

namespace tgon
{

void GenericApplication::ShowOkPopup(const char* message, const char* caption, OkPopupEventHandler onMessageBoxEventHandled)
{
    MessageBoxA(nullptr, message, caption, MB_OK);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled();
    }
}

void GenericApplication::ShowYesNoPopup(const char* message, const char* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxA(nullptr, message, caption, MB_YESNO);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

void WindowsApplication::ShowYesNoPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxW(nullptr, message, caption, MB_YESNO);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

void WindowsApplication::ShowOkPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler onMessageBoxEventHandled)
{
    auto clickedBtnType = MessageBoxW(nullptr, message, caption, MB_OK);

    if (onMessageBoxEventHandled != nullptr)
    {
        onMessageBoxEventHandled(static_cast<YesNoPopupEvent>(clickedBtnType));
    }
}

void WindowsApplication::EnableFloatException(unsigned int flag)
{
    unsigned int currentFlag;
    _controlfp_s(&currentFlag, 0, 0);

    unsigned int newFlag = currentFlag;
    newFlag &= ~flag;
    _controlfp_s(&currentFlag, newFlag, MCW_EM);
}

HINSTANCE WindowsApplication::GetInstanceHandle()
{
    static HINSTANCE instanceHandle = GetModuleHandle(nullptr);
    return instanceHandle;
}
    
} /* namespace tgon */