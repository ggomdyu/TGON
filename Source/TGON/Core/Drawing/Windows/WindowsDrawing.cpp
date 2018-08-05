#include "PrecompiledHeader.h"

#include <Windows.h>

#include "../Drawing.h"

namespace tgon
{

void DrawPoint(Window& window, const Point& p)
{
    HWND wndHandle = reinterpret_cast<HWND>(window.GetNativeWindow());
    HDC dcHandle = ::GetDC(wndHandle);
    {
        SetPixel(dcHandle, p.x, p.y, RGB(0, 0, 0));
    }
    ::ReleaseDC(wndHandle, dcHandle);
}

void DrawLine(Window& window, const Point& p1, const Point& p2)
{
    HWND wndHandle = reinterpret_cast<HWND>(window.GetNativeWindow());
    HDC dcHandle = ::GetDC(wndHandle);
    {
        ::MoveToEx(dcHandle, p1.x, p1.y, RGB(0, 0, 0));
        ::LineTo(dcHandle, p2.x, p2.y);
    }
    ::ReleaseDC(wndHandle, dcHandle);
}

void DrawPolygon(Window& window, const Point& p1, const Point& p2, const Point& p3)
{
    const POINT ptTable[3] =
    {
        {p1.x, p1.y},
        {p2.x, p2.y},
        {p3.x, p3.y},
    };

    HWND wndHandle = reinterpret_cast<HWND>(window.GetNativeWindow());
    HDC dcHandle = ::GetDC(wndHandle);
    {
        ::Polygon(dcHandle, ptTable, 3);
    }
    ::ReleaseDC(wndHandle, dcHandle);
}

} /* namespace tgon */