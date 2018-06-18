/**
 * @file    Mouse.h
 * @author  ggomdyu
 * @since   05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"

namespace tgon
{
    
class InputManager;
class MouseImpl;
enum class MouseCode;
    
class TGON_API Mouse final
{
/* @section Public constructor */
public:
    explicit Mouse(InputManager* inputManager);
    
/* @section Public destructor */
public:
    ~Mouse();
    
/* @section Public method */
public:
    void Update();
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const MouseImpl* GetImpl() const noexcept;
    MouseImpl* GetImpl() noexcept;
    
/* @section Private variable */
private:
    std::unique_ptr<MouseImpl> m_impl;
};
    
} /* namespace tgon */
