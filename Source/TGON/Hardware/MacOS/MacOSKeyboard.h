/**
 * @file    MacOSKeyboard.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"

namespace gainput
{
    
class InputDeviceKeyboard;
    
} /* namespace gainput */

namespace tgon
{
    
enum class KeyCode;
    
class TGON_API MacOSKeyboard :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit MacOSKeyboard(gainput::InputDeviceKeyboard* nativeKeyboard);
    
/**@section Method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const gainput::InputDeviceKeyboard* GetNativeKeyboard() const noexcept;
    gainput::InputDeviceKeyboard* GetNativeKeyboard() noexcept;
    
/**@section Variable */
private:
    gainput::InputDeviceKeyboard* m_nativeKeyboard;
};
    
using PlatformKeyboard = MacOSKeyboard;

} /* namespace tgon */
