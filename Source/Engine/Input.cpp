#include "PrecompiledHeader.h"

#include "Input.h"

namespace tg
{

Input::Input(const InputMode& inputMode) :
    m_keyboard(inputMode.isUseKeyboard ? m_inputManager.CreateKeyboard() : nullptr),
    m_mouse(inputMode.isUseMouse ? m_inputManager.CreateMouse() : nullptr)
{
}

bool Input::GetKey(KeyCode key) const noexcept
{
    return m_keyboard->IsKeyHold(key);
}

bool Input::GetKeyDown(KeyCode key) const noexcept
{
    return m_keyboard->IsKeyDown(key);
}

bool Input::GetKeyUp(KeyCode key) const noexcept
{
    return m_keyboard->IsKeyUp(key);
}

bool Input::GetMouseButton(int32_t button) const noexcept
{
    constexpr MouseCode mouseCodeTable[] = {
        MouseCode::Left,
        MouseCode::Right,
        MouseCode::Middle
    };

    return m_mouse->IsMouseHold(mouseCodeTable[button]);
}

bool Input::GetMouseButtonDown(int32_t button) const noexcept
{
    constexpr MouseCode mouseCodeTable[] = {
        MouseCode::Left,
        MouseCode::Right,
        MouseCode::Middle
    };

    return m_mouse->IsMouseDown(mouseCodeTable[button]);
}

bool Input::GetMouseButtonUp(int32_t button) const noexcept
{
    constexpr MouseCode mouseCodeTable[] = {
        MouseCode::Left,
        MouseCode::Right,
        MouseCode::Middle
    };

    return m_mouse->IsMouseUp(mouseCodeTable[button]);
}

void Input::Update()
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
}

}
