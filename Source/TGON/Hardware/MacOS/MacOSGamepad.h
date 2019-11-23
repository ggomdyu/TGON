/**
 * @file    MacOSGamepad.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <gainput/gainput.h>

#include "Core/NonCopyable.h"
#include "Platform/Config.h"

namespace tgon
{
    
class MacOSGamepad :
    private NonCopyable
{
/**@section Constructor */
public:
    explicit MacOSGamepad(gainput::InputDevicePad* nativeGamepad);
    
/**@section Method */
public:
    gainput::InputDevicePad* GetNativeGamepad() noexcept;
    const gainput::InputDevicePad* GetNativeGamepad() const noexcept;
    
/**@section Variable */
protected:
    gainput::InputDevicePad* m_nativeGamepad;
};
    
using PlatformGamepad = MacOSGamepad;

} /* namespace tgon */
