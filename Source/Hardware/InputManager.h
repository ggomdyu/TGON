#pragma once

#include <memory>

#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

namespace tg
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
    std::shared_ptr<Keyboard> CreateKeyboard() const;
    std::shared_ptr<Mouse> CreateMouse() const;
    std::shared_ptr<Gamepad> CreateGamePad() const;

/**@section Variable */
protected:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};

}
