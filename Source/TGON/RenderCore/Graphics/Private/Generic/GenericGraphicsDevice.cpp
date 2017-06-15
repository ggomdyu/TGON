#include "PrecompiledHeader.h"
#include "GenericGraphicsDevice.h"

namespace tgon
{
namespace graphics
{

GenericGraphicsDevice::GenericGraphicsDevice(const platform::TSharedWindow& surfaceWindow) :
    m_surfaceWindow(surfaceWindow)
{
}

const TRefreshRate& GenericGraphicsDevice::GetRefreshRate() const noexcept
{
    return m_refreshRate;
}

uint32_t GenericGraphicsDevice::GetVendorId() const noexcept
{
    return m_vendorID;
}

uint32_t GenericGraphicsDevice::GetVideoMemorySize() const noexcept
{
    return m_videoMemoryMiB;
}

platform::TSharedWindow& GenericGraphicsDevice::GetSurfaceWindow() noexcept
{
	return m_surfaceWindow;
}

const string::TFixedString& GenericGraphicsDevice::GetVideoCardDescription() const noexcept
{
    return m_videoCardDescription;
}

} /* namespace graphics */
} /* namespace tgon */