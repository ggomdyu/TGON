/**
 * @filename    Mouse.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#include "MouseFwd.h"

namespace tgon
{
    
class TGON_API Mouse final
{
/* @section Public constructor */
public:
    explicit Mouse(InputManager* inputManager);
    
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
    std::shared_ptr<MouseImpl> m_impl;
};
    
} /* namespace tgon */