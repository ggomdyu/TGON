/**
 * @filename    InputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <memory>

#include "Core/Platform/Config.h"

namespace tgon
{

class Window;
class InputManagerImpl;

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
    
    const InputManagerImpl* GetImpl() const noexcept;
    InputManagerImpl* GetImpl() noexcept;
    
/* @section Private variable */
private:
    std::unique_ptr<InputManagerImpl> m_impl;
};

} /* namespace tgon */
