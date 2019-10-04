#include "PrecompiledHeader.h"

#include "Texture.h"

namespace tgon
{

PlatformTexture& Texture::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformTexture& Texture::GetPlatformDependency() const noexcept
{
    return *this;
}

Texture::Texture(Texture&& rhs) noexcept :
    PlatformTexture(std::move(rhs)),
    m_isUseMipmap(rhs.m_isUseMipmap),
    m_isDynamicUsage(rhs.m_isDynamicUsage),
    m_pixelFormat(rhs.m_pixelFormat),
    m_filterMode(rhs.m_filterMode),
    m_wrapMode(rhs.m_wrapMode),
    m_size(rhs.m_size)
{
    rhs.m_isUseMipmap = false;
    rhs.m_isDynamicUsage = false;
    rhs.m_pixelFormat = {};
    rhs.m_filterMode = {};
    rhs.m_wrapMode = {};
    rhs.m_size = {};
}

Texture& Texture::operator=(Texture&& rhs)
{
    PlatformTexture::operator=(std::move(rhs));
    
    m_isUseMipmap = rhs.m_isUseMipmap;
    m_isDynamicUsage = rhs.m_isDynamicUsage;
    m_pixelFormat = rhs.m_pixelFormat;
    m_filterMode = rhs.m_filterMode;
    m_wrapMode = rhs.m_wrapMode;
    m_size = rhs.m_size;

    rhs.m_isUseMipmap = false;
    rhs.m_isDynamicUsage = false;
    rhs.m_pixelFormat = {};
    rhs.m_filterMode = {};
    rhs.m_wrapMode = {};
    rhs.m_size = {};

    return *this;
}

} /* namespace tgon */
