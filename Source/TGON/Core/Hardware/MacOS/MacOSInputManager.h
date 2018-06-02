/**
 * @filename    InputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <memory>

#include "Mouse.h"
#include "Keyboard.h"

namespace tgon
{

class InputManager final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    InputManager();
    
/* @section Public method */
public:
    void Update();
    
    std::unique_ptr<Mouse> CreateMouse() const;
    std::unique_ptr<Keyboard> CreateKeyboard() const;
//    Gamepad     CreateGamepad();
    
private:
    std::unique_ptr<gainput::InputManager> m_inputManager;
};

} /* namespace tgon */
