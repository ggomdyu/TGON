/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include "Platform/Window.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

namespace tgon
{

class TGON_API InputManager final :
    private PlatformInputManager
{
/**@section Constructor */
public:
    explicit InputManager(const Window& inputTargetWindow);

/**@section Destructor */
public:
    ~InputManager();

/**@section Method */
public:
    PlatformInputManager& GetPlatformDependency() noexcept;
    const PlatformInputManager& GetPlatformDependency() const noexcept;
    void Update();
};

}
