#include "PrecompiledHeader.h"

#include "Core/Hardware/Keyboard.h"
#include "Core/Hardware/Mouse.h"
#include "Core/Hardware/Gamepad.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const std::shared_ptr<Window>& inputTarget, const InputMode& inputMode) :
    m_inputManager(inputTarget),
    m_keyboard(inputMode.isUseKeyboard ? m_inputManager.CreateKeyboard() : nullptr),
    m_mouse(inputMode.isUseMouse ? m_inputManager.CreateMouse() : nullptr),
    m_gamepad(inputMode.isUseGamepad ? m_inputManager.CreateGamepad() : nullptr)
{
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
