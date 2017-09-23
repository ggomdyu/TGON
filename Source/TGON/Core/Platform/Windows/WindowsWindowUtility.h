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
 * @brief                       Create window via given arguments.
 * @param [in] windowStyle		The Style information
 * @param [in] className		The class-name which registered via RegisterClass
 * @param [in] instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param [in] extraParam		Extra data for window
 */
HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className = L"TGON", void* extraParam = nullptr);

/**
 * @note                Copy and paste window placement information ( e.g. Position, Size, Window style )
 * @param [in] from     Paste target
 * @param [in] to       Destination of copied target
 */
void CopyAndPasteWindowShape(const class WindowsWindow& from, const class WindowsWindow& to);

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */
