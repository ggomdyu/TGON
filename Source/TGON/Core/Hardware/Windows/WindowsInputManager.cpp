#include "PrecompiledHeader.h"

#include "WindowsInputManager.h"

namespace tgon
{
   
WindowsInputManager::WindowsInputManager(const std::shared_ptr<Window>& inputTarget) :
    m_inputManager(OIS::InputManager::createInputSystem(this->QueryParamList(inputTarget)))
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

OIS::Mouse* WindowsInputManager::CreateNativeMouse()
{
    return static_cast<OIS::Mouse*>(m_inputManager->createInputObject(OIS::OISMouse, true));
}

OIS::Keyboard* WindowsInputManager::CreateNativeKeyboard()
{
    return static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
}

OIS::JoyStick* WindowsInputManager::CreateNativeGamepad()
{
    return static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true));
}

OIS::ParamList WindowsInputManager::QueryParamList(const std::shared_ptr<Window>& inputTarget) const
{
    OIS::ParamList paramList
    {
        {"WINDOW", std::to_string(reinterpret_cast<size_t>(inputTarget->GetNativeWindow()))}
    };

    return paramList;
}

} /* namespace tgon */
