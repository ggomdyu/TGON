#include "PrecompiledHeader.h"

#include "InputManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Gamepad.h"

namespace tgon
{

std::unique_ptr<Mouse> InputManager::CreateMouse()
{
    return std::make_unique<Mouse>(this->CreateNativeMouse());
}

std::unique_ptr<Keyboard> InputManager::CreateKeyboard()
{
    return std::make_unique<Keyboard>(this->CreateNativeKeyboard());
}

std::unique_ptr<Gamepad> InputManager::CreateGamepad()
{
    return std::make_unique<Gamepad>(this->CreateNativeGamepad());
}

} /* namespace tgon */
