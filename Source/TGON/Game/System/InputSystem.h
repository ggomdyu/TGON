/**
 * @filename    InputSystem.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <gainput/gainput.h>

#include "Core/Math/Extent.h"

#include "ISystem.h"

namespace tgon
{

struct InputSystemProperty
{
    bool isUseKeyboard = false;
    bool isUseMouse = false;
    bool isUseGamepad = false;
};

class TGON_API InputSystem :
    public ISystem
{
/* @section Public constructor */
public:
    InputSystem();

/* @section Public destructor */
public:
    virtual ~InputSystem() override;

/* @section Public method */
public:
    void Initialize(const I32Extent2D& displaySize, const InputSystemProperty& inputSystemProperty);

    virtual void Update() override;

/* @section Private variable */
public:
    gainput::InputManager m_inputManager;
};

} /* namespace tgon */