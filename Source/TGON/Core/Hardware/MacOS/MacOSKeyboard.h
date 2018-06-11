/**
 * @filename    MacOSKeyboard.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "MacOSKeyboardType.h"

namespace tgon
{
    
class MacOSKeyboard :
    public GenericKeyboard
{
public:
    TGON_RUNTIME_OBJECT(MacOSKeyboard);
    
/* @section Public constructor */
public:
    explicit MacOSKeyboard(gainput::InputDeviceKeyboard* keyboardDevice) noexcept;

/* @section Public destructor */
public:
    virtual ~MacOSKeyboard() override = default;
    
/* @section Public method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    MacOSKeyboard* GetPlatformService();
    const MacOSKeyboard* GetPlatformService() const;
    gainput::InputDeviceKeyboard* GetKeyboardDevice();
    const gainput::InputDeviceKeyboard* GetKeyboardDevice() const;

/* @section Private variable */
private:
    gainput::InputDeviceKeyboard* m_keyboardDevice;
};

} /* namespace tgon */
