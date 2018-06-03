#include "PrecompiledHeader.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const InputMode& inputMode, const std::shared_ptr<GenericWindow>& inputTargetWindow) :
    m_inputManager(inputTargetWindow)
{
    if (inputMode.isUseKeyboard)
    {
        m_keyboard = m_inputManager.CreateKeyboard();
    }
    
    if (inputMode.isUseMouse)
    {
        m_mouse = m_inputManager.CreateMouse();
    }

    if (inputMode.isUseGamepad)
    {
        m_gamepad = m_inputManager.CreateGamepad();
    }
}
    
void InputModule::Update()
{
    m_inputManager.Update();

    if (m_keyboard != nullptr)
    {
        m_keyboard->Update();
    }

    if (m_mouse != nullptr)
    {
        m_mouse->Update();
    }

    if (m_gamepad != nullptr)
    {
        m_gamepad->Update();
    }
}

const std::unique_ptr<Mouse>& InputModule::GetMouse() const
{
    return m_mouse;
}

const std::unique_ptr<Keyboard>& InputModule::GetKeyboard() const
{
    return m_keyboard;
}

const std::unique_ptr<Gamepad>& InputModule::GetGamepad() const
{
    return m_gamepad;
}

} /* namespace tgon */
