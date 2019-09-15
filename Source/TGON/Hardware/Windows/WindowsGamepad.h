/**
 * @file    WindowsGamepad.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <OIS.h>

#include "Core/NonCopyable.h"

namespace tgon
{

enum class GamepadPov
{
    Left,
    Up,
    Down,
    Right,
    LeftUp,
    LeftDown,
};

class TGON_API WindowsGamepad :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit WindowsGamepad(OIS::JoyStick* nativeGamepad) noexcept;

/**@section Method */
public:
    OIS::JoyStick* GetNativeGamepad() noexcept;
    const OIS::JoyStick* GetNativeGamepad() const noexcept;

/**@section Variable */
protected:
    OIS::JoyStick* m_nativeGamepad;
    OIS::JoyStickState m_prevGamepadState;
};

using PlatformGamepad = WindowsGamepad;

} /* namespace tgon */