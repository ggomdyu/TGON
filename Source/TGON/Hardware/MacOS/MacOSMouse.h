/**
 * @file    MacOSMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#import <boost/noncopyable.hpp>
#import <gainput/gainput.h>
#import <cstdint>

#import "Platform/Config.h"

namespace tgon
{

enum class MouseCode
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

class TGON_API MacOSMouse :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit MacOSMouse(gainput::InputDeviceMouse* nativeMouse) noexcept;
    
/**@section Method */
public:
    gainput::InputDeviceMouse* GetNativeMouse() noexcept;
    const gainput::InputDeviceMouse* GetNativeMouse() const noexcept;
    
/**@section Variable */
protected:
    gainput::InputDeviceMouse* m_nativeMouse;
};
    
using PlatformMouse = MacOSMouse;
    
} /* namespace tgon */
