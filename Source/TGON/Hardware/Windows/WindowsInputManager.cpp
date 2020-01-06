#include "PrecompiledHeader.h"

#include "../InputManager.h"

#ifdef _MSC_VER
#   pragma comment(lib, "dxguid.lib")
#   pragma comment(lib, "dinput8.lib")
#endif

namespace tgon
{

WindowsInputManager::WindowsInputManager(const Window& inputTarget) :
    m_inputManager(OIS::InputManager::createInputSystem(reinterpret_cast<size_t>(inputTarget.GetNativeWindow())))
{
    m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
}

WindowsInputManager::WindowsInputManager(WindowsInputManager&& rhs) noexcept :
    m_inputManager(rhs.m_inputManager)
{
    rhs.m_inputManager = nullptr;
}

WindowsInputManager::~WindowsInputManager()
{
    if (m_inputManager != nullptr)
    {
        OIS::InputManager::destroyInputSystem(m_inputManager);
        m_inputManager = nullptr;
    }
}

OIS::Mouse* WindowsInputManager::CreateNativeMouse()
{
    return reinterpret_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
}

OIS::Keyboard* WindowsInputManager::CreateNativeKeyboard()
{
    return reinterpret_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
}

OIS::JoyStick* WindowsInputManager::CreateNativeGamepad()
{
    return reinterpret_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true));
}

OIS::InputManager* WindowsInputManager::GetInputManager() noexcept
{
    return m_inputManager;
}

const OIS::InputManager* WindowsInputManager::GetInputManager() const noexcept
{
    return m_inputManager;
}

void InputManager::Update()
{
}

} /* namespace tgon */
