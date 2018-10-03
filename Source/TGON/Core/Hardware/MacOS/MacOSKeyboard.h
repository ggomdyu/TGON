/**
 * @file    MacOSKeyboard.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace gainput
{
    
class InputDeviceKeyboard;
    
} /* namespace gainput */

namespace tgon
{
    
enum class KeyCode;
class InputManagerImpl;
    
class TGON_API KeyboardImpl final :
    private boost::noncopyable
{
/**@section Public constructor */
public:
    explicit KeyboardImpl(InputManagerImpl& platformInputManager);
    
/**@section Public method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const gainput::InputDeviceKeyboard* GetKeyboardDevice() const noexcept;
    gainput::InputDeviceKeyboard* GetKeyboardDevice() noexcept;
    
/**@section Private variable */
private:
    gainput::InputDeviceKeyboard* m_keyboardDevice;
};

} /* namespace tgon */
