#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{

WindowsInputManager::WindowsInputManager(OIS::InputManager* inputManager) noexcept :
    m_inputManager(inputManager)
{
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

OIS::ParamList WindowsInputManager::QueryParamList(const Window& inputTargetWindow) const
{
    OIS::ParamList paramList
    {
        {"WINDOW", std::to_string(reinterpret_cast<size_t>(inputTargetWindow.GetNativeWindow()))}
    };

    return paramList;
}

OIS::InputManager* WindowsInputManager::GetInputManager() noexcept
{
    return m_inputManager;
}

const OIS::InputManager* WindowsInputManager::GetInputManager() const noexcept
{
    return m_inputManager;
}

InputManager::InputManager(const Window& inputTargetWindow) :
    WindowsInputManager(OIS::InputManager::createInputSystem(QueryParamList(inputTargetWindow)))
{
    m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
}

InputManager::~InputManager()
{
    OIS::InputManager::destroyInputSystem(m_inputManager);
    m_inputManager = nullptr;
}

void InputManager::Update()
{
}

} /* namespace tgon */
