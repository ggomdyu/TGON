#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "InputManager.h"

namespace tg
{

InputManager::InputManager() :
    m_inputManager(std::make_unique<gainput::InputManager>())
{

#if TGON_PLATFORM_WINDOWS
    Application::GetInstance().GetPlatformDependency().SetMessageHandler([](const MSG& msg, void* param)
    {
        reinterpret_cast<gainput::InputManager*>(param)->HandleMessage(msg);
    }, m_inputManager.get());
#endif
}

std::shared_ptr<Keyboard> InputManager::CreateKeyboard() const
{
    return std::make_shared<Keyboard>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>());
}

std::shared_ptr<Mouse> InputManager::CreateMouse() const
{
    return std::make_shared<Mouse>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>());
}

std::shared_ptr<Gamepad> InputManager::CreateGamePad() const
{
    return std::make_shared<Gamepad>(m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>());
}

void InputManager::Update()
{
    m_inputManager->Update();
}

}
