#include "PrecompiledHeader.h"

#include <OIS.h>

#include "Core/Platform/Window.h"

#include "WindowsInputManager.h"

namespace tgon
{
   
InputManagerImpl::InputManagerImpl(std::shared_ptr<Window> inputTarget) :
    m_inputManager(OIS::InputManager::createInputSystem(QueryParamList(inputTarget)))
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

OIS::Mouse* InputManagerImpl::CreateMouseDevice()
{
    return static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
}

OIS::Keyboard* InputManagerImpl::CreateKeyboardDevice()
{
    return static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
}

OIS::JoyStick* InputManagerImpl::CreateGamepadDevice()
{
    return static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true));
}

OIS::ParamList InputManagerImpl::QueryParamList(std::shared_ptr<Window> inputTarget) const
{
    OIS::ParamList paramList
    {
        {"WINDOW", std::to_string(reinterpret_cast<size_t>(inputTarget->GetNativeWindow()))}
    };

    return paramList;
}

} /* namespace tgon */
