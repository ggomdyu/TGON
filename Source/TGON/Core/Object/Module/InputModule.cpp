#include "PrecompiledHeader.h"

#include "Core/Hardware/InputManager.h"

#include "InputModule.h"

namespace tgon
{
    
constexpr InputMode::InputMode(bool isUseKeyboard, bool isUseMouse, bool isUseGamepad) noexcept :
    isUseKeyboard(isUseKeyboard),
    isUseMouse(isUseMouse),
    isUseGamepad(isUseGamepad)
{
}

InputModule::InputModule(const InputMode& inputMode, const std::shared_ptr<Window>& inputTarget) :
    m_inputManager(inputTarget)
{
    if (inputMode.isUseKeyboard)
    {
        m_keyboard = std::make_unique<Keyboard>(&m_inputManager);
    }
    
    if (inputMode.isUseMouse)
    {
        m_mouse = std::make_unique<Mouse>(&m_inputManager);
    }

    if (inputMode.isUseGamepad)
    {
        m_gamepad = std::make_unique<Gamepad>(&m_inputManager);
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
