/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

namespace tgon
{

class TGON_API InputManager final :
    private boost::noncopyable
{
/**@section Public constructor */
public:
    InputManager(const std::shared_ptr<Window>& inputTarget);
    
/**@section Public destructor */
public:
    ~InputManager();
    
/**@section Public method */
public:
    void Update();
    
    const InputManagerImpl& GetImpl() const noexcept;
    InputManagerImpl& GetImpl() noexcept;
    
/**@section Private variable */
private:
    InputManagerImpl m_inputManagerImpl;
};

} /* namespace tgon */
