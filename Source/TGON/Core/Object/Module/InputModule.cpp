#include "PrecompiledHeader.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const InputMode& inputMode, const std::shared_ptr<GenericWindow>& inputTargetWindow) :
    m_inputManager(inputTargetWindow)
{
    if (inputMode.isUseKeyboard)
    {
        m_keyboard = std::make_unique<Keyboard>(m_inputManager.CreateKeyboard());
    }
    
    if (inputMode.isUseMouse)
    {
        m_mouse = std::make_unique<Mouse>(m_inputManager.CreateMouse());
    }

    if (inputMode.isUseGamepad)
    {
        m_gamepad = std::make_unique<Gamepad>(m_inputManager.CreateGamepad());
    }
}
    
void InputModule::Update()
{
    m_inputManager.Update();

    if (m_keyboard != nullptr)
    {
        m_keyboard->Update();
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
