#include "PrecompiledHeader.h"

#include "Platform/Application.h"

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager()
{
    m_inputManager = std::make_unique<gainput::InputManager>();

    Application::GetInstance().GetPlatformDependency().SetMessageHandler([](const MSG& msg)
    {
        m_inputManager->HandleMessage(msg);
    });
}

InputManager::~InputManager()
{
    m_inputManager.release();
}

std::shared_ptr<Keyboard> InputManager::CreateKeyboard()
{
    return std::make_shared<Keyboard>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>());
}

std::shared_ptr<Mouse> InputManager::CreateMouse()
{
    return std::make_shared<Mouse>(m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>());
}

std::shared_ptr<Gamepad> InputManager::CreateGamePad()
{
    return std::make_shared<Gamepad>(m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>());
}

void InputManager::Update()
{
    m_inputManager->Update();
}

} /* namespace tgon */
