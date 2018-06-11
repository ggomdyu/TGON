/**
 * @filename    WindowsMouse.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "WindowsMouseType.h"

namespace tgon
{

class WindowsMouse :
    public GenericMouse
{
/* @section Public constructor */
public:
    explicit WindowsMouse(OIS::Mouse* mouseDevice) noexcept;

/* @section Public destructor */
public:
    virtual ~WindowsMouse() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    virtual bool IsMouseDown(MouseCode mouseCode) const override;
    virtual bool IsMouseHold(MouseCode mouseCode) const override;
    virtual bool IsMouseUp(MouseCode mouseCode) const override;

/* @section Private variable */
private:
    OIS::Mouse* m_mouseDevice;
    OIS::MouseState m_prevMouseState;
};

using Mouse = WindowsMouse;

} /* namespace tgon */
