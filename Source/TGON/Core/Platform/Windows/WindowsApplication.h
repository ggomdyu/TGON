/**
 * @filename    WindowsApplication.h
 * @author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "../Generic/GenericApplication.h"

#include "WindowsApplicationType.h"

namespace tgon
{

class WindowsApplication :
    public GenericApplication
{
/**
 * @section Ctor/Dtor
 */
public:
    WindowsApplication() = delete;
    ~WindowsApplication() = delete;

/**
 * @section Public command method
 */
public:
    /**
     * @brief                   Shows the Message box which has buttons: Yes, No
     * @param [in] message      Message box description
     * @param [in] caption      Message box title
     * @param [in] handler      Button click event handler
     */ 
    static void ShowYesNoPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler handler);

    /**
     * @brief                   Show the Message box which has Ok button
     * @param [in] message      Message box description
     * @param [in] caption      Message box title
     * @param [in] handler      Button click event handler
     */ 
    static void ShowOkPopup(const wchar_t* message, const wchar_t* caption, YesNoPopupEventHandler handler);

    /**
     * @brief                   Enables floating operation exception.
     * @param [in] flag         Flag you want to enable: EM_OVERFLOW, EM_UNDERFLOW, EM_ZERODIVIDE, etc
     */
    static void EnableFloatException(unsigned int flag);

/**
 * @section Get method
 */
public:
    static HINSTANCE GetInstanceHandle();
};

using TApplication = WindowsApplication;

} /* namespace tgon */
