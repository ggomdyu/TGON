#include "PrecompiledHeader.h"

#include "InputSystem.h"

namespace tgon
{

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem() = default;

void InputSystem::Initialize(const I32Extent2D& displaySize, const InputSystemProperty& inputSystemProperty)
{
    m_inputManager.SetDisplaySize(displaySize.width, displaySize.height);

    if (inputSystemProperty.isUseKeyboard)
    {
        
    }

    if (inputSystemProperty.isUseMouse)
    {
    }

    if (inputSystemProperty.isUseGamepad)
    {
    }
}

void InputSystem::Update()
{
    m_inputManager.Update();
}

}