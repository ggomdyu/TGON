/**
 * @file    WindowsMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <OIS.h>

#include "Platform/Config.h"

namespace tgon
{

enum class MouseCode
{
    Mouse0  = OIS::MB_Left,
    Mouse1  = OIS::MB_Right,
    Mouse2  = OIS::MB_Middle,
    Mouse3  = OIS::MB_Button3,
    Mouse4  = OIS::MB_Button4,
    Mouse5  = OIS::MB_Button5,
    Mouse6  = OIS::MB_Button6,
    Mouse7  = OIS::MB_Button7,
    Mouse8,
    Mouse9,
    Mouse10,
    Mouse11,
    Mouse12,
    Mouse13,
    Mouse14,
    Mouse15,
    Mouse16,
    Mouse17,
    Mouse18,
    Mouse19,
    Mouse20,
    Left = Mouse0,
    Middle = Mouse1,
    Right = Mouse2,
    WheelUp = Mouse3,
    WheelDown = Mouse4,
};

class TGON_API WindowsMouse :
    private boost::noncopyable
{
/**@section Constructor */
protected:
    explicit WindowsMouse(OIS::Mouse* nativeMouse) noexcept;
    
/**@section Method */
public:
    OIS::Mouse* GetNativeMouse() noexcept;
    const OIS::Mouse* GetNativeMouse() const noexcept;

/**@section Variable */
protected:
    OIS::Mouse* m_nativeMouse;
    OIS::MouseState m_currMouseState;
};

using PlatformMouse = WindowsMouse;

}
