/**
 * @file    WindowsMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/Platform/Config.h"

#include "WindowsMouseType.h"

namespace OIS
{

class Mouse;
class MouseState;

}

namespace tgon
{

class WindowsInputManager;

class TGON_API WindowsMouse :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsMouse(OIS::Mouse* nativeMouse) noexcept;

/**@section Method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const OIS::Mouse* GetNativeMouse() const;
    OIS::Mouse* GetNativeMouse();

/**@section Variable */
private:
    OIS::Mouse* m_nativeMouse;
    std::shared_ptr<OIS::MouseState> m_currMouseState;
};

using PlatformMouse = WindowsMouse;

} /* namespace tgon */
