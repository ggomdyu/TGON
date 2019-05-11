/**
 * @file    MacOSGamepad.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>

#include "Platform/Config.h"

namespace gainput
{
    
class InputDevicePad;
    
} /* namespace gainput */

namespace tgon
{
    
class TGON_API MacOSGamepad :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit MacOSGamepad(gainput::InputDevicePad* nativeGamepad);
    
/**@section Method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const gainput::InputDevicePad* GetNativeGamepad() const noexcept;
    gainput::InputDevicePad* GetNativeGamepad() noexcept;
    
/**@section Variable */
private:
    gainput::InputDevicePad* m_nativeGamepad;
};
    
using PlatformGamepad = MacOSGamepad;

} /* namespace tgon */
