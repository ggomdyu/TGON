/**
 * @filename    Mouse.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <gainput/gainput.h>

namespace tgon
{

class Mouse final :
    private boost::noncopyable
{
/* @section Puiblic enum */
public:
    enum class MouseCode : std::underlying_type_t<gainput::MouseButton>
    {
        Mouse0      = gainput::MouseButton0,
        Mouse1      = gainput::MouseButton1,
        Mouse2      = gainput::MouseButton2,
        Mouse3      = gainput::MouseButton3,
        Mouse4      = gainput::MouseButton4,
        Mouse5      = gainput::MouseButton5,
        Mouse6      = gainput::MouseButton6,
        Mouse7      = gainput::MouseButton7,
        Mouse8      = gainput::MouseButton8,
        Mouse9      = gainput::MouseButton9,
        Mouse10     = gainput::MouseButton10,
        Mouse11     = gainput::MouseButton11,
        Mouse12     = gainput::MouseButton12,
        Mouse13     = gainput::MouseButton13,
        Mouse14     = gainput::MouseButton14,
        Mouse15     = gainput::MouseButton15,
        Mouse16     = gainput::MouseButton16,
        Mouse17     = gainput::MouseButton17,
        Mouse18     = gainput::MouseButton18,
        Mouse19     = gainput::MouseButton19,
        Mouse20     = gainput::MouseButton20,
        Left        = Mouse0,
        Middle      = Mouse1,
        Right       = Mouse2,
        WheelUp     = Mouse3,
        WheelDown   = Mouse4,
    };

/* @section Public constructor */
public:
    explicit Mouse(gainput::InputDeviceMouse* mouseDevice) noexcept;

/* @section Public method */
public:
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
//    float GetAxisX() const;
//    float GetAxisY() const;

/* @section Private variable */
private:
    gainput::InputDeviceMouse* m_mouseDevice;
};

} /* namespace tgon */
