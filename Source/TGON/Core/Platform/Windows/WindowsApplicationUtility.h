/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       02/13/2018
 */

#pragma once
#include "Core/Utility/Algorithm.h"

#include "WindowsApplication.h"

namespace tgon
{

inline UINT ConvertMessageBoxIconTypeToNative(MessageBoxIconType messageBoxIconType) noexcept
{
    static constexpr const UINT nativeMessageBoxIconTypeTable[] =
    {
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };

    return nativeMessageBoxIconTypeTable[UnderlyingCast(messageBoxIconType)];
}

/* @brief   Register default WNDCLASS to window class table. */
inline bool RegisterWindowClass()
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = sizeof(void*);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpfnWndProc = WindowsApplication::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}


} /* namespace tgon */