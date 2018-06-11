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
    explicit MacOSMouse(gainput::InputDeviceMouse* mouseDevice) noexcept;
    
/* @section Public destructor */
public:
    virtual ~MacOSMouse() override = default;

/* @section Public method */
public:
    virtual void Update() final override;
    virtual void GetPosition(int32_t* x, int32_t* y) const final override;
    virtual float GetFloat(MouseCode mouseCode) const final override;
    virtual bool IsMouseDown(MouseCode mouseCode) const final override;
    virtual bool IsMouseHold(MouseCode mouseCode) const final override;
    virtual bool IsMouseUp(MouseCode mouseCode) const final override;

/* @section Private variable */
private:
    gainput::InputDeviceMouse* m_mouseDevice;
};
    
using Mouse = MacOSMouse;

} /* namespace tgon */
