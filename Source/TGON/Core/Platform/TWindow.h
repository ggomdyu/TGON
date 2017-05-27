/**
 * @filename    PlatformWindow.h
 * @author      ggomdyu
 * @since       04/01/2016
 */

#pragma once
#include <boost/predef/os.h>
#include <memory>

#include "Core/Utility/TTypeTraits.h"

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsWindow.h"
#elif BOOST_OS_ANDROID
#	include "Android/AndroidWindow.h"
#endif

namespace tgon {
namespace platform {

template <typename WindowTy, typename... Args, typename = utility::EnableIfConvertible<WindowTy*, TWindow*>>
std::shared_ptr<WindowTy> MakeWindow(Args&&... args)
{
    return std::make_shared<WindowTy>(std::forward<Args>(args)...);
}

using TSharedWindow = std::shared_ptr<platform::TWindow>;

} /* namespace platform */
} /* namespace tgon */