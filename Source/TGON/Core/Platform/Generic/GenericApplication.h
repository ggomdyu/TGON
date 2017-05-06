/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include "GenericApplicationType.h"

#include "Core/Platform/TConfig.h"

namespace tgon {
namespace platform {

/**
 * @brief                   Show a popup with Ok button
 * @param [in] message      Popup description text
 * @param [in] caption      Popup title text
 * @param [in] handler      Button click event handler
 */
TGON_API void ShowOkPopup(const char* message);
TGON_API void ShowOkPopup(const char* message, OkPopupEventHandler handler);
TGON_API void ShowOkPopup(const char* message, const char* caption);
TGON_API void ShowOkPopup(const char* message, const char* caption, OkPopupEventHandler handler);

/**
 * @brief                   Show a popup with buttons: Yes, No
 * @param [in] message      Popup description text
 * @param [in] caption      Popup title text
 * @param [in] handler      Button click event handler
 */
TGON_API void ShowYesNoPopup(const char* message);
TGON_API void ShowYesNoPopup(const char* message, YesNoPopupEventHandler handler);
TGON_API void ShowYesNoPopup(const char* message, const char* caption);
TGON_API void ShowYesNoPopup(const char* message, const char* caption, YesNoPopupEventHandler handler);

} /* namespace platform */
} /* namespace tgon */