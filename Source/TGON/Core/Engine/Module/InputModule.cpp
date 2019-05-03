#include "PrecompiledHeader.h"

#include "Core/Hardware/Keyboard.h"
#include "Core/Hardware/Mouse.h"
#include "Core/Hardware/Gamepad.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const std::shared_ptr<Window>& inputTarget, const InputMode& inputMode) :
    m_inputManager(inputTarget)
{
    if (inputMode.isUseKeyboard)
    {
        m_keyboard = std::make_unique<Keyboard>(m_inputManager);
    }
    
    if (inputMode.isUseMouse)
    {
        m_mouse = std::make_unique<Mouse>(m_inputManager);
    }

    if (inputMode.isUseGamepad)
    {
        m_gamepad = std::make_unique<Gamepad>(m_inputManager);
    }
}
    
InputModule::~InputModule() = default;
   
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

const std::unique_ptr<Mouse>& InputModule::GetMouse() const noexcept
{
    return m_mouse;
}

const std::unique_ptr<Keyboard>& InputModule::GetKeyboard() const noexcept
{
    return m_keyboard;
}

const std::unique_ptr<Gamepad>& InputModule::GetGamepad() const noexcept
{
    return m_gamepad;
}

} /* namespace tgon */
