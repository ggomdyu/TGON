/**
 * @file    MacOSGamepad.h
 * @author  ggomdyu
 * @since   06/03/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <gainput/gainput.h>

#include "Platform/Config.h"

namespace tgon
{
    
class TGON_API MacOSGamepad :
    private boost::noncopyable
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
