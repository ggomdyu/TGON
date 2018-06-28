#include "PrecompiledHeader.h"

#include "InputManager.h"
#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

namespace tgon
{

InputManager::InputManager(const Window& inputTarget) :
    m_inputManagerImpl(std::make_unique<InputManagerImpl>(inputTarget))
{
}
    
InputManager::~InputManager() = default;

void InputManager::Update()
{
    m_inputManagerImpl->Update();
}

const InputManagerImpl& InputManager::GetImpl() const noexcept
{
    return *m_inputManagerImpl;
}

InputManagerImpl& InputManager::GetImpl() noexcept
{
    return *m_inputManagerImpl;
}

} /* namespace tgon */
