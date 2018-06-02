#include "PrecompiledHeader.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule(const InputMode& inputMode)
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
    }
}
    
void InputModule::Update()
{
    m_inputManager.Update();
}

const std::unique_ptr<Keyboard>& InputModule::GetKeyboard() const
{
    return m_keyboard;
}

const std::unique_ptr<Mouse>& InputModule::GetMouse() const
{
    return m_mouse;
}

} /* namespace tgon */
