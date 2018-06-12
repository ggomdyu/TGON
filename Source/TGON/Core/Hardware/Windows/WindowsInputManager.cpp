#include "PrecompiledHeader.h"

#include <OIS.h>

#include "Core/Platform/Window.h"

#include "WindowsInputManager.h"

namespace tgon
{
   
InputManagerImpl::InputManagerImpl(const Window& window) :
    m_inputManager(OIS::InputManager::createInputSystem(QueryParamList(window)))
{
    m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
}

InputManagerImpl::~InputManagerImpl()
{
    OIS::InputManager::destroyInputSystem(m_inputManager);
}

void InputManagerImpl::Update()
{
}

OIS::Mouse* InputManagerImpl::CreateMouse()
{
    return static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
}

OIS::Keyboard* InputManagerImpl::CreateKeyboard()
{
    return static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
}

OIS::JoyStick* InputManagerImpl::CreateGamepad()
{
    return static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true));
}

OIS::ParamList InputManagerImpl::QueryParamList(const Window& window) const
{
    OIS::ParamList paramList
    {
        {"WINDOW", std::to_string(reinterpret_cast<size_t>(window.GetNativeWindow()))}
    };

    return paramList;
}

} /* namespace tgon */