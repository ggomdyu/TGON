#include "PrecompiledHeader.h"

#if TGON_PLATFORM_WINDOWS
#   include <Windows.h>
#elif TGON_PLATFORM_MACOS
#   include <AppKit/AppKit.h>
#endif

#include "Core/Algorithm.h"
#include "Platform/Application.h"

#include "Mouse.h"

namespace tgon
{

Mouse::Mouse(gainput::InputDeviceMouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}

Mouse::Mouse(Mouse&& rhs) noexcept :
    m_nativeMouse(rhs.m_nativeMouse)
{
    rhs.m_nativeMouse = nullptr;
}

Mouse& Mouse::operator=(Mouse&& rhs) noexcept
{
    m_nativeMouse = rhs.m_nativeMouse;

    rhs.m_nativeMouse = nullptr;

    return *this;
}

void Mouse::Update()
{
}

I32Vector2 Mouse::GetPosition()
{
    I32Vector2 pt;
    Mouse::GetPosition(&pt.x, &pt.y);

    return pt;
}

void Mouse::GetPosition(int32_t* x, int32_t* y)
{
#if TGON_PLATFORM_WINDOWS
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(reinterpret_cast<HWND>(Application::GetInstance().GetRootWindow()->GetNativeWindow()), &pt);

    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
#elif TGON_PLATFORM_MACOS
    NSPoint pt = [NSEvent mouseLocation];
    pt.y = [NSScreen mainScreen].frame.size.height - pt.y;
    
    *x = static_cast<int32_t>(pt.x);
    *y = static_cast<int32_t>(pt.y);
#else
    *x = 0;
    *y = 0;
#endif
}

bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) == false &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
