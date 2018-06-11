#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"
#include "Core/Utility/Algorithm.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsKeyboard.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSKeyboard.h"
#endif

#include "Keyboard.h"

namespace tgon
{
    
Keyboard::Keyboard(InputManager* inputManager) :
    m_impl(std::make_shared<KeyboardImpl>(inputManager))
{
//    assert(keyboardDevice != nullptr && "keyboardDevice can't be nullptr.");
}
    
void Keyboard::Update()
{
    m_impl->Update();
}
    
bool Keyboard::IsKeyDown(KeyCode keyCode) const
{
    return m_impl->IsKeyDown(keyCode);
}
    
bool Keyboard::IsKeyHold(KeyCode keyCode) const
{
    return m_impl->IsKeyHold(keyCode);
}
    
bool Keyboard::IsKeyUp(KeyCode keyCode) const
{
    return m_impl->IsKeyUp(keyCode);
}
    
KeyboardImpl* Keyboard::GetImpl() noexcept
{
    return m_impl.get();
}

const KeyboardImpl* Keyboard::GetImpl() const noexcept
{
    return m_impl.get();
}

} /* namespace tgon */
