#include "PrecompiledHeader.h"

#include "Keyboard.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif
#include "InputManager.h"

namespace tgon
{
    
Keyboard::Keyboard(InputManager& inputManager) :
    m_keyboardImpl(std::make_unique<KeyboardImpl>(inputManager.GetImpl()))
{
}
    
Keyboard::~Keyboard() = default;
    
void Keyboard::Update()
{
    m_keyboardImpl->Update();
}
    
bool Keyboard::IsKeyDown(KeyCode keyCode) const
{
    return m_keyboardImpl->IsKeyDown(keyCode);
}
    
bool Keyboard::IsKeyHold(KeyCode keyCode) const
{
    return m_keyboardImpl->IsKeyHold(keyCode);
}
    
bool Keyboard::IsKeyUp(KeyCode keyCode) const
{
    return m_keyboardImpl->IsKeyUp(keyCode);
}
    
KeyboardImpl& Keyboard::GetImpl() noexcept
{
    return *m_keyboardImpl;
}

const KeyboardImpl& Keyboard::GetImpl() const noexcept
{
    return *m_keyboardImpl;
}

} /* namespace tgon */
