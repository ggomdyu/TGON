/**
 * filename GenericApplication.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "../../TConfig.h"

#include "GenericApplicationFwd.h"

namespace tgon
{

template <typename PlatformApplicationTy>
class TGON_API GenericApplication :
    private PlatformApplicationTy
{
public:
	GenericApplication() = delete;
	~GenericApplication() = delete;

public:
    static void ShowYesNoPopup(const char* message);
    static void ShowYesNoPopup(const char* message, OnPopupEventHandle handler);
    static void ShowOkPopup(const char* message);
    static void ShowOkPopup(const char* message, OnPopupEventHandle handler);
};

template<typename PlatformApplicationTy>
inline void GenericApplication<PlatformApplicationTy>::ShowYesNoPopup(const char* message)
{
    PlatformApplicationTy::ShowYesNoPopup(message, "", nullptr);
}

template<typename PlatformApplicationTy>
inline void GenericApplication<PlatformApplicationTy>::ShowYesNoPopup(const char* message, OnPopupEventHandle onMessageBoxEventHandled)
{
    PlatformApplicationTy::ShowYesNoPopup(message, "", onMessageBoxEventHandled);
}

template<typename PlatformApplicationTy>
inline void GenericApplication<PlatformApplicationTy>::ShowOkPopup(const char* message)
{
    PlatformApplicationTy::ShowOkPopup(message, "", nullptr);
}

template<typename PlatformApplicationTy>
inline void GenericApplication<PlatformApplicationTy>::ShowOkPopup(const char* message, OnPopupEventHandle onMessageBoxEventHandled)
{
    PlatformApplicationTy::ShowOkPopup(message, "", onMessageBoxEventHandled);
}

} /* namespace tgon */