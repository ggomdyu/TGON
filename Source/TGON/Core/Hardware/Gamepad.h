/**
 * @filename    Gamepad.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <memory>
#include <cstdint>

#include "Core/Platform/Config.h"

#include "GamepadFwd.h"

namespace tgon
{
    
class TGON_API Gamepad final
{
/* @section Public constructor */
public:
    explicit Gamepad(InputManager* inputManager);
    
/* @section Public destructor */
public:
    ~Gamepad();
    
/* @section Public method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const GamepadImpl* GetImpl() const noexcept;
    GamepadImpl* GetImpl() noexcept;
    
/* @section Private variable */
private:
    std::unique_ptr<GamepadImpl> m_impl;
};
    
} /* namespace tgon */
