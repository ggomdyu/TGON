/**
 * @file    WindowsWindowUtility.h
 * @author  ggomdyu
 * @since   11/12/2015
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <windows.h>

#include "Core/Platform/Config.h"

#include "../WindowType.h"

namespace tgon
{

class TGON_API WindowsWindowUtility
{
/**@section Public method */
public:
    /**
     * @brief                       Creates a window through given arguments.
     * @param [in] windowStyle		The style information for the window to be created.
     * @param [in] instanceHandle	The handle of process.
     * @param [in] className		The class name to be used to initialize the window attributes.
     * @param [in] extraParam		The extra data that window will have.
     */
    static HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className = L"TGON", void* extraParam = nullptr);

/**@section Private method */
private:
    static void ConverWindowStyleToNative(const WindowStyle& windowStyle, DWORD* rawWindowStyle, DWORD* rawExtendedWindowStyle);
};

} /* namespace tgon */