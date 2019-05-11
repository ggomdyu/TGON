/**
 * @file    WindowsKeyboard.h
 * @author  ggomdyu
 * @since   06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"

namespace OIS
{
    
class Keyboard;
    
} /* namespace OIS */

namespace tgon
{
    
enum class KeyCode;
class WindowsInputManager;

class TGON_API WindowsKeyboard :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsKeyboard(OIS::Keyboard* nativeKeyboard);

/**@section Method */
public:
    void Update();
    bool IsKeyDown(KeyCode keyCode) const;
    bool IsKeyHold(KeyCode keyCode) const;
    bool IsKeyUp(KeyCode keyCode) const;
    const OIS::Keyboard* GetNativeKeyboard() const noexcept;
    OIS::Keyboard* GetNativeKeyboard() noexcept;
    
/**@section Variable */
private:
    OIS::Keyboard* m_nativeKeyboard;
    char m_currKeyStates[256];
};

using PlatformKeyboard = WindowsKeyboard;

} /* namespace tgon */
