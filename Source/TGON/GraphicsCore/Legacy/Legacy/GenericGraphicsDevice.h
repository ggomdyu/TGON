/**
 * @filename    GenericGraphicsDevice.h
 * @author      ggomdyu
 * @since       04/02/2017
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "GenericGraphicsDeviceType.h"

#include "Core/String/TFixedString.h"
#include "Core/Platform/TWindow.h"

namespace tgon {
namespace graphics {

class TGON_API GenericGraphicsDevice :
    private boost::noncopyable
{
/**
 * @section Ctor/Dtor
 */
public:
    explicit GenericGraphicsDevice(const platform::TSharedWindow& surfaceWindow);
    ~GenericGraphicsDevice() = default;

/**
 * @section Get method
 */
public:
	platform::TSharedWindow& GetSurfaceWindow() noexcept;
    const string::TFixedString& GetVideoCardDescription() const noexcept;
    const TRefreshRate& GetRefreshRate() const noexcept;
    uint32_t GetVendorId() const noexcept;
    /* @return  Current device's Video memory in MiB */
    uint32_t GetVideoMemorySize() const noexcept;

/**
 * @section Private variable
 */
protected:
    platform::TSharedWindow m_surfaceWindow;
    string::TFixedString m_videoCardDescription;
    TRefreshRate m_refreshRate;
    uint32_t m_vendorID;
    uint32_t m_videoMemoryMiB;
};

} /* namespace graphics */
} /* namespace tgon */