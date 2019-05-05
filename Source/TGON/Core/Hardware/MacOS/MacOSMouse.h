/**
 * @file    MacOSMouse.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <cstdint>

#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDeviceMouse;

} /* namespace gainput */

namespace tgon
{

class WindowsInputManager;
enum class MouseCode;
    
class TGON_API WindowsMouse final :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsMouse(WindowsInputManager& inputManagerImpl);
    
/**@section Method */
public:
    void Update();
    static void GetPosition(int32_t* x, int32_t* y);
    //float GetFloat(MouseCode mouseCode) const;
    bool IsMouseDown(MouseCode mouseCode) const;
    bool IsMouseHold(MouseCode mouseCode) const;
    bool IsMouseUp(MouseCode mouseCode) const;
    const gainput::InputDeviceMouse* GetMouseDevice() const noexcept;
    gainput::InputDeviceMouse* GetNativeMouse() noexcept;
    
    /**@section Variable */
private:
    gainput::InputDeviceMouse* m_nativeMouse;
};
    
} /* namespace tgon */
