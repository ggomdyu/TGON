#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{
   
WindowsInputManager::WindowsInputManager(const std::shared_ptr<GenericWindow>& window) :
    m_inputManager(OIS::InputManager::createInputSystem(QueryParamList(window)))
{
    m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
}

WindowsInputManager::~WindowsInputManager()
{
    OIS::InputManager::destroyInputSystem(m_inputManager);
}

void WindowsInputManager::Update()
{
}

OIS::ParamList WindowsInputManager::QueryParamList(const std::shared_ptr<GenericWindow>& window) const
{
    OIS::ParamList paramList
    {
        {"WINDOW", std::to_string(reinterpret_cast<size_t>(window->GetNativeWindow()))}
    };

    return paramList;
}

std::unique_ptr<Keyboard> InputManager::CreateKeyboard()
{
    return std::make_unique<Keyboard>(static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true)));
}

std::unique_ptr<Mouse> InputManager::CreateMouse()
{
    return std::make_unique<Mouse>(static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true)));
}

std::unique_ptr<Gamepad> InputManager::CreateGamepad()
{
    return std::make_unique<Gamepad>(static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true)));
}

} /* namespace tgon */
