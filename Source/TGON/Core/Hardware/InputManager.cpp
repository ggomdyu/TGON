#include "PrecompiledHeader.h"

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager(const Window& inputTarget) :
    m_inputManagerImpl(inputTarget)
{
}
    
InputManager::~InputManager() = default;

void InputManager::Update()
{
    m_inputManagerImpl.Update();
}

const InputManagerImpl& InputManager::GetImpl() const noexcept
{
    return m_inputManagerImpl;
}

InputManagerImpl& InputManager::GetImpl() noexcept
{
    return m_inputManagerImpl;
}

} /* namespace tgon */
