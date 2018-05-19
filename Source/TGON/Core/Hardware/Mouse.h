/**
 * @filename    Mouse.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "InputManager.h"

namespace tgon
{

class Mouse final :
    private boost::noncopyable
{
/* @section Puiblic enum */
public:
    enum class KeyCode : gainput::UserButtonId
    {
        Button0,
        Left = Button0,
        Button1,
        Middle = Button1,
        Button2,
        Right = Button2,
        Button3,
        WheelUp = Button3,
        Button4,
        WheelDown = Button4,
        Button5,
        Button6,
        Button7,
        Button8,
        Button9,
        Button10,
        Button11,
        Button12,
        Button13,
        Button14,
        Button15,
        Button16,
        Button17,
        Button18,
        Button19,
        Button20,
    };

/* @section Public method */
public:
    static bool IsKeyDown(KeyCode keyCode) noexcept;
    static bool IsKeyUp(KeyCode keyCode) noexcept;
    static void UpdateKeyStates();
};

} /* namespace tgon */