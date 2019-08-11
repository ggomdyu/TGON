/**
 * @file    Mouse.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Point.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif

#include "InputManager.h"

namespace tgon
{
    
class TGON_API Mouse final :
    private PlatformMouse
{
/**@section Constructor */
public:
    explicit Mouse(InputManager& inputManager);

/**@section Method */
public:
    PlatformMouse& GetPlatformDependency() noexcept;
    const PlatformMouse& GetPlatformDependency() const noexcept;
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    static I32Point GetPosition();
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
};
    
} /* namespace tgon */
