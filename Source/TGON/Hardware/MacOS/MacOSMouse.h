/**
 * @file    MacOSMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>

#include "Platform/Config.h"

namespace gainput
{
    
class InputDeviceMouse;

} /* namespace gainput */

namespace tgon
{

enum class MouseCode;
    
class TGON_API MacOSMouse :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit MacOSMouse(gainput::InputDeviceMouse* nativeMouse) noexcept;
    
/**@section Method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const gainput::InputDeviceMouse* GetNativeMouse() const noexcept;
    gainput::InputDeviceMouse* GetNativeMouse() noexcept;
    
    /**@section Variable */
private:
    gainput::InputDeviceMouse* m_nativeMouse;
};
    
using PlatformMouse = MacOSMouse;
    
} /* namespace tgon */
