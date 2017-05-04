/**
 * @filename    GenericApplication.h
 * @author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "GenericApplicationType.h"

#include "Core/Platform/TConfig.h"

namespace tgon
{

class TGON_API GenericApplication
{
/**
 * @section Ctor/Dtor
 */
public:
    GenericApplication() = delete;
    ~GenericApplication() = delete;

/**
 * @section Public command method
 */
public:
    /**
     * @brief                   Show a popup with Ok button
     * @param [in] message      Popup description text
     * @param [in] caption      Popup title text
     * @param [in] handler      Button click event handler
     */
    static void ShowOkPopup(const char* message);
    static void ShowOkPopup(const char* message, OkPopupEventHandler handler);
    static void ShowOkPopup(const char* message, const char* caption);
    static void ShowOkPopup(const char* message, const char* caption, OkPopupEventHandler handler);

    /**
     * @brief                   Show a popup with buttons: Yes, No
     * @param [in] message      Popup description text
     * @param [in] caption      Popup title text
     * @param [in] handler      Button click event handler
     */
    static void ShowYesNoPopup(const char* message);
    static void ShowYesNoPopup(const char* message, YesNoPopupEventHandler handler);
    static void ShowYesNoPopup(const char* message, const char* caption);
    static void ShowYesNoPopup(const char* message, const char* caption, YesNoPopupEventHandler handler);
};

} /* namespace tgon */