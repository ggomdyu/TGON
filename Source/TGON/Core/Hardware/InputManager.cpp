#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsInputManager.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSInputManager.h"
#endif

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager(const Window& inputTargetWindow) :
    m_impl(std::make_unique<InputManagerImpl>(inputTargetWindow))
{
}
    
InputManager::~InputManager() = default;

void InputManager::Update()
{
    m_impl->Update();
}

const InputManagerImpl* InputManager::GetImpl() const noexcept
{
    return m_impl.get();
}

InputManagerImpl* InputManager::GetImpl() noexcept
{
    return m_impl.get();
}

} /* namespace tgon */
