#include "PrecompiledHeader.h"

#include "Texture.h"

namespace tgon
{

Texture::Texture(const char* filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    Texture(Image(filePath), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

Texture::Texture(const Image& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    Texture(image.GetData(), image.GetSize(), image.GetPixelFormat(), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
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

Texture::~Texture()
{
    this->Destroy();
}

Texture& Texture::operator=(Texture&& rhs)
{
    this->Destroy();

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

PlatformTexture& Texture::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformTexture& Texture::GetPlatformDependency() const noexcept
{
    return *this;
}

void Texture::SetFilterMode(FilterMode filterMode)
{
    m_filterMode = filterMode;
}

void Texture::SetWrapMode(WrapMode wrapMode)
{
    m_wrapMode = wrapMode;
}

FilterMode Texture::GetFilterMode() const noexcept
{
    return m_filterMode;
}

WrapMode Texture::GetWrapMode() const noexcept
{
    return m_wrapMode;
}

const I32Extent2D& Texture::GetSize() const noexcept
{
    return m_size;
}
    
PixelFormat Texture::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

} /* namespace tgon */
