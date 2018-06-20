#include "PrecompiledHeader.h"

#include "Keyboard.h"
#include "InputManager.h"

namespace tgon
{
    
Keyboard::Keyboard(InputManager& inputManager) :
    m_platformKeyboard(inputManager.GetPlatformDependency())
{
}
    
Keyboard::~Keyboard() = default;
    
void Keyboard::Update()
{
    m_platformKeyboard.Update();
}
    
bool Keyboard::IsKeyDown(KeyCode keyCode) const
{
    return m_platformKeyboard.IsKeyDown(keyCode);
}
    
bool Keyboard::IsKeyHold(KeyCode keyCode) const
{
    return m_platformKeyboard.IsKeyHold(keyCode);
}
    
bool Keyboard::IsKeyUp(KeyCode keyCode) const
{
    return m_platformKeyboard.IsKeyUp(keyCode);
}
    
PlatformKeyboard& Keyboard::GetPlatformDependency() noexcept
{
    return m_platformKeyboard;
}

const PlatformKeyboard& Keyboard::GetPlatformDependency() const noexcept
{
    return m_platformKeyboard;
}

} /* namespace tgon */
