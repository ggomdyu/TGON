/**
 * @filename    MacOSMouse.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "MacOSMouseType.h"

namespace tgon
{

class MacOSMouse :
    public GenericMouse
{
/* @section Public constructor */
public:
    explicit MacOSMouse(void* mouseDevice) noexcept;
    
/* @section Public destructor */
public:
    virtual ~MacOSMouse() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    using GenericMouse::GetPosition;
    virtual bool IsMouseDown(MouseCode mouseCode) const override;
    virtual bool IsMouseHold(MouseCode mouseCode) const override;
    virtual bool IsMouseUp(MouseCode mouseCode) const override;

/* @section Private variable */
private:
    gainput::InputDeviceMouse* m_mouseDevice;
};
    
using Mouse = MacOSMouse;

} /* namespace tgon */
