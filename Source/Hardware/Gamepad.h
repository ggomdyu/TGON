#pragma once

#include <gainput/gainput.h>

#include "Core/NonCopyable.h"

namespace tg
{

class Gamepad final :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit Gamepad(gainput::InputDevicePad* nativeGamePad) noexcept;
    Gamepad(Gamepad&& rhs) noexcept;
    
/**@section Operator */
public:
    Gamepad& operator=(Gamepad&& rhs) noexcept;

/**@section Method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;

/**@section Variable */
private:
    gainput::InputDevicePad* m_nativeGamepad;
};
    
}
