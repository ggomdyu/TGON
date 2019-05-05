/**
 * @file    WindowsGamepad.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>
#include <OIS.h>

#include "Core/Platform/Config.h"

#include "WindowsGamepadType.h"

namespace tgon
{

class TGON_API WindowsGamepad :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsGamepad(OIS::JoyStick* nativeGamepad);

/**@section Method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const OIS::JoyStick* GetNativeGamepad() const noexcept;
    OIS::JoyStick* GetNativeGamepad() noexcept;

/**@section Variable */
private:
    OIS::JoyStick* m_nativeGamepad;
    OIS::JoyStickState m_prevGamepadState;
};

using PlatformGamepad = WindowsGamepad;

} /* namespace tgon */