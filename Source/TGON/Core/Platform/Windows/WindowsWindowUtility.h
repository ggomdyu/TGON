/**
 * @filename    WindowsWindowUtility.h
 * @author   ggomdyu
 * since    11/12/2015
 */

#pragma once
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <windows.h>

namespace tgon {
namespace window {

/**
    * @note                        Convert WindowStyle to DWORD.
    * @param [in] normalWndStyle   Normal window style (e.g. WS_...)
    * @param [in] exWndStyle       Extended window style (e.g. WS_EX_...)
    */
void ConvertWindowStyleToDword(const struct WindowStyle& wndStyle, DWORD* exWndStyle, DWORD* normalWndStyle);

/**
 * @note                        Create window by forwarded arguments
 * @param [in] wndStyle		    Window style which described about form
 * @param [in] className		Window class name which registered via RegisterClass ( You can forward defaultly WindowsPlatformApplication::AppClassName )
 * @param [in] instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param [in] extraParam		Extra data for window
 */
HWND CreateWindowForm(const struct WindowStyle& wndStyle, const wchar_t* className, HINSTANCE instanceHandle, void* extraParam = nullptr);

/**
 * @note                Copy and paste window placement information ( e.g. Position, Size, Window style )
 * @param [in]  from    Paste target
 * @param [in]  to      Destination of copied target
 */
void ReshapeWindowForm(const class WindowsWindow& from, const class WindowsWindow& to);

// Todo: 윈도우클래스로 옮기자. 최소단위의 기능이기에 객체지향을 해치지 않는다고 예상됨.
bool HasSystemMenu(const class WindowsWindow& window);

} /* namespace window */
} /* namespace tgon */