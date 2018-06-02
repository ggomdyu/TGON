#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#include "WindowsInputManager.h"

namespace tgon
{
   
WindowsInputManager::WindowsInputManager(const std::shared_ptr<GenericWindow>& window) :
    m_inputManager(OIS::InputManager::createInputSystem(QueryParamList(window)))
{
    m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
}

void* WindowsInputManager::CreateKeyboard() const
{
    return m_inputManager->createInputObject(OIS::OISKeyboard, true);
}

void* WindowsInputManager::CreateMouse() const
{
    return m_inputManager->createInputObject(OIS::OISMouse, true);
}

void* WindowsInputManager::CreateGamepad() const
{
    return m_inputManager->createInputObject(OIS::OISJoyStick, true);
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

} /* namespace tgon */
