#include "PrecompiledHeader.h"

#include "Texture.h"

namespace tgon
{

Texture::Texture(const Image& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    Texture(image.GetImageData(), image.GetSize(), image.GetPixelFormat(), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

Texture::Texture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    PlatformTexture(),
    m_isUseMipmap(isUseMipmap),
    m_isDynamicUsage(isDynamicUsage),
    m_pixelFormat(pixelFormat),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_size(size)
{
    this->SetData(imageData, size, pixelFormat);
}

Texture::Texture(void* nativeTexture) noexcept :
    PlatformTexture(nativeTexture)
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
}

Texture& Texture::operator=(Texture&& rhs) noexcept
{
    PlatformTexture::operator=(std::move(rhs));
    
    m_isUseMipmap = rhs.m_isUseMipmap;
    m_isDynamicUsage = rhs.m_isDynamicUsage;
    m_pixelFormat = rhs.m_pixelFormat;
    m_filterMode = rhs.m_filterMode;
    m_wrapMode = rhs.m_wrapMode;
    m_size = rhs.m_size;

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

void Texture::Use()
{
    if (g_lastUsedTexture == this)
    {
        return;
    }

    PlatformTexture::Use();
    g_lastUsedTexture = this;
}

void Texture::Unuse()
{
    PlatformTexture::Unuse();
    g_lastUsedTexture = nullptr;
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

const void* Texture::GetNativeTexture() const noexcept
{
    return const_cast<Texture*>(this)->GetNativeTexture();
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
