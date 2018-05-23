/**
 * @filename    InputModule.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <gainput/gainput.h>

#include "Core/Math/Extent.h"

#include "Core/Object/IModule.h"

namespace tgon
{

struct InputModuleProperty
{
    bool isUseKeyboard = false;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

class TGON_API InputModule :
    public IModule
{
/* @section Public constructor */
public:
    InputModule();

/* @section Public destructor */
public:
    virtual ~InputModule() override;

/* @section Public method */
public:
    void Initialize(const I32Extent2D& displaySize, const InputModuleProperty& InputModuleProperty);

    virtual void Update() override;

/* @section Private variable */
public:
    gainput::InputManager m_inputManager;
};

} /* namespace tgon */