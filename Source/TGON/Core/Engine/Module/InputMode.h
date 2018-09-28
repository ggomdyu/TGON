/**
 * @file    InputMode.h
 * @author  ggomdyu
 * @since   09/15/2018
 */

#pragma once

namespace tgon
{

struct InputMode final
{
/* @section Public constructor */
public:
    constexpr InputMode() noexcept = default;

    constexpr InputMode(bool isUseKeyboard, bool isUseMouse, bool isUseGamepad) noexcept;
    
/* @section Public variable */
public:
    bool isUseKeyboard = true;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

constexpr InputMode::InputMode(bool isUseKeyboard, bool isUseMouse, bool isUseGamepad) noexcept :
    isUseKeyboard(isUseKeyboard),
    isUseMouse(isUseMouse),
    isUseGamepad(isUseGamepad)
{
}

} /* namespace tgon */
