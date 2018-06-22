/**
 * @file    MacOSMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDeviceMouse;

} /* namespace gainput */

namespace tgon
{

class MacOSInputManager;
enum class MouseCode;
    
class TGON_API MacOSMouse final
{
/* @section Public constructor */
public:
    explicit MacOSMouse(MacOSInputManager& inputManagerImpl);
    
/* @section Public method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    //float GetFloat(MouseCode mouseCode) const;
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const gainput::InputDeviceMouse* GetMouseDevice() const noexcept;
    gainput::InputDeviceMouse* GetMouseDevice() noexcept;
    
    /* @section Private variable */
private:
    gainput::InputDeviceMouse* m_mouseDevice;
};
    
using PlatformMouse = MacOSMouse;

} /* namespace tgon */
