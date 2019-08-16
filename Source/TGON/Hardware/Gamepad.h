/**
 * @file    Gamepad.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsGamepad.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSGamepad.h"
#endif

#include "InputManager.h"

namespace tgon
{

class TGON_API Gamepad final :
    private PlatformGamepad
{
/**@section Constructor */
public:
    explicit Gamepad(InputManager& inputManager);

/**@section Method */
public:
    PlatformGamepad& GetPlatformDependency() noexcept;
    const PlatformGamepad& GetPlatformDependency() const noexcept;
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
};
    
} /* namespace tgon */
