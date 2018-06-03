/**
 * @filename    WindowsMouseType.h
 * @author      ggomdyu
 * @since       06/03/2018
 */

#pragma once
#include <OIS.h>

#include "../Generic/GenericMouse.h"

namespace tgon
{

enum class GenericMouse::MouseCode
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

} /* namespace tgon */
