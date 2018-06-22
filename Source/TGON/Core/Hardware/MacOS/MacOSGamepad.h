/**
 * @file    MacOSGamepad.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDevicePad;
    
} /* namespace gainput */

namespace tgon
{
    
class MacOSInputManager;

class TGON_API MacOSGamepad final
{
/* @section Public constructor */
public:
    explicit MacOSGamepad(MacOSInputManager& inputManagerImpl);
    
/* @section Public method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const gainput::InputDevicePad* GetGamepadDevice() const noexcept;
    gainput::InputDevicePad* GetGamepadDevice() noexcept;
    
/* @section Private variable */
private:
    gainput::InputDevicePad* m_gamepadDevice;
};

using PlatformGamepad = MacOSGamepad;

} /* namespace tgon */
