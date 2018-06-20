/**
 * @file    Mouse.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Math/Point.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsMouse.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSMouse.h"
#endif

namespace tgon
{
    
class InputManager;
enum class MouseCode;
    
class TGON_API Mouse final
{
/* @section Public constructor */
public:
    explicit Mouse(InputManager& inputManager);
    
/* @section Public destructor */
public:
    ~Mouse();
    
/* @section Public method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    static I32Point GetPosition();
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const PlatformMouse& GetPlatformDependency() const noexcept;
    PlatformMouse& GetPlatformDependency() noexcept;
    
/* @section Private variable */
private:
    PlatformMouse m_platformMouse;
};
    
} /* namespace tgon */
