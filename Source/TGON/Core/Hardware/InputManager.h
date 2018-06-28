/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <memory>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace tgon
{

class Window;
class InputManagerImpl;

class TGON_API InputManager final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    InputManager(const Window& inputTarget);
    
/* @section Public destructor */
public:
    ~InputManager();
    
/* @section Public method */
public:
    void Update();
    
    const InputManagerImpl& GetImpl() const noexcept;
    InputManagerImpl& GetImpl() noexcept;
    
/* @section Private variable */
private:
    std::unique_ptr<InputManagerImpl> m_inputManagerImpl;
};

} /* namespace tgon */
