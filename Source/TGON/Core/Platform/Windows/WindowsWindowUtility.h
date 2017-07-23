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

namespace tgon
{
namespace platform
{

struct WindowStyle;

namespace windows
{

/**
 * @brief                       Converts WindowStyle to Native-window-style.
 * @param [in] windowStyle		Window style information
 * @param [out] extendedStyle   Extended window style (e.g. WS_EX_...)
 * @param [out] normalStyle     Normal window style (e.g. WS_...)
 */
void ConvertToNativeWindowStyle(const WindowStyle& windowStyle, DWORD* extendedStyle, DWORD* normalStyle);

/**
 * @brief                       Create window via given arguments.
 * @param [in] windowStyle		Window style information
 * @param [in] className		Window class name which registered via RegisterClass ( You can forward defaultly WindowsPlatformApplication::AppClassName )
 * @param [in] instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param [in] extraParam		Extra data for window
 */
HWND CreateNativeWindow(const WindowStyle& windowStyle, const wchar_t* className, HINSTANCE instanceHandle, void* extraParam = nullptr);

/**
 * @note                Copy and paste window placement information ( e.g. Position, Size, Window style )
 * @param [in] from     Paste target
 * @param [in] to       Destination of copied target
 */
void ReshapeWindowForm(const class WindowsWindow& from, const class WindowsWindow& to);

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */
