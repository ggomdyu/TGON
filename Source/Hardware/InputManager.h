/**
 * @file    InputManager.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

namespace tgon
{

class InputManager final :
    private NonCopyable
{
/**@section Constructor */
public:
    InputManager();

/**@section Method */
public:
    void Update();
    std::shared_ptr<Keyboard> CreateKeyboard();
    std::shared_ptr<Mouse> CreateMouse();
    std::shared_ptr<Gamepad> CreateGamePad();

/**@section Variable */
protected:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};

} /* namespace tgon */
