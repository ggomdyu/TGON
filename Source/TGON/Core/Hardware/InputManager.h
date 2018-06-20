/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <memory>

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

namespace tgon
{

class Window;

class TGON_API InputManager final
{
/* @section Public constructor */
public:
    InputManager(std::shared_ptr<Window> inputTarget);
    
/* @section Public destructor */
public:
    ~InputManager();
    
/* @section Public method */
public:
    void Update();
    
    const PlatformInputManager& GetPlatformDependency() const noexcept;
    PlatformInputManager& GetPlatformDependency() noexcept;
    
/* @section Private variable */
private:
    PlatformInputManager m_platformInputManager;
};

} /* namespace tgon */
