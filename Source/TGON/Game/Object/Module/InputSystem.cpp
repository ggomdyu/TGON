#include "PrecompiledHeader.h"

#include "InputModule.h"

namespace tgon
{

InputModule::InputModule()
{
}

InputModule::~InputModule() = default;

void InputModule::Initialize(const I32Extent2D& displaySize, const InputModuleProperty& InputModuleProperty)
{
    m_inputManager.SetDisplaySize(displaySize.width, displaySize.height);

    if (InputModuleProperty.isUseKeyboard)
    {
        
    }

    if (InputModuleProperty.isUseMouse)
    {
    }

    if (InputModuleProperty.isUseGamepad)
    {
    }
}

void InputModule::Update()
{
    m_inputManager.Update();
}

}