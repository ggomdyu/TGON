/**
 * @filename    WindowsWindowUtility.h
 * @author      ggomdyu
 * @since       11/12/2015
 */

#pragma once
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <windows.h>

namespace tgon {
namespace platform {

struct TWindowStyle;

namespace windows {

/**
 * @brief                       Convert TWindowStyle to DWORD.
 * @param [out] extendedStyle   Extended window style (e.g. WS_EX_...)
 * @param [out] normalStyle     Normal window style (e.g. WS_...)
 */
void ConvertWindowStyleToDword(const TWindowStyle& wndStyle, DWORD* extendedStyle, DWORD* normalStyle);

/**
 * @note                        Create window by forwarded arguments
 * @param [in] wndStyle		    Window style which described about form
 * @param [in] className		Window class name which registered via RegisterClass ( You can forward defaultly WindowsPlatformApplication::AppClassName )
 * @param [in] instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param [in] extraParam		Extra data for window
 */
HWND CreateWindowForm(const TWindowStyle& wndStyle, const wchar_t* className, HINSTANCE instanceHandle, void* extraParam = nullptr);

/**
 * @note                Copy and paste window placement information ( e.g. Position, Size, Window style )
 * @param [in] from     Paste target
 * @param [in] to       Destination of copied target
 */
void ReshapeWindowForm(const class WindowsWindow& from, const class WindowsWindow& to);

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */