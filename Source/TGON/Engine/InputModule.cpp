#include "PrecompiledHeader.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const Window& inputTarget, const InputMode& inputMode) :
    m_inputManager(inputTarget),
    m_keyboard(inputMode.isUseKeyboard ? std::make_shared<Keyboard>(m_inputManager) : nullptr),
    m_mouse(inputMode.isUseMouse ? std::make_shared<Mouse>(m_inputManager) : nullptr),
    m_gamepad(inputMode.isUseGamepad ? std::make_shared<Gamepad>(m_inputManager) : nullptr)
{
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

std::shared_ptr<Mouse> InputModule::GetMouse() noexcept
{
    return m_mouse;
}

std::shared_ptr<const Mouse> InputModule::GetMouse() const noexcept
{
    return m_mouse;
}

std::shared_ptr<Keyboard> InputModule::GetKeyboard() noexcept
{
    return m_keyboard;
}

std::shared_ptr<const Keyboard> InputModule::GetKeyboard() const noexcept
{
    return m_keyboard;
}

std::shared_ptr<Gamepad> InputModule::GetGamepad() noexcept
{
    return m_gamepad;
}

std::shared_ptr<const Gamepad> InputModule::GetGamepad() const noexcept
{
    return m_gamepad;
}

}
