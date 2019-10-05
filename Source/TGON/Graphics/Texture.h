/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include "Math/Vector2.h"
#include "Drawing/Image.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{

enum class FilterMode
{
    Point,
    Bilinear,
};

enum class WrapMode
{
    Repeat,
    Clamp,
    Mirror,
};

class TGON_API Texture :
    private PlatformTexture
{
/**@section Constructor */
public:
    Texture(const std::string_view& filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    Texture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    Texture(const Image& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    Texture(Texture&& rhs) noexcept;

/**@section Destructor */
public:
    ~Texture();
    
/**@section Operator */
public:
    Texture& operator=(Texture&& rhs);
  
/**@section Method */
public:
    PlatformTexture& GetPlatformDependency() noexcept;
    const PlatformTexture& GetPlatformDependency() const noexcept;
    void Use();
    void Unuse();
    bool IsValid() const;
    void SetData(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetData(const std::byte* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetFilterMode(FilterMode filterMode);
    void SetWrapMode(WrapMode wrapMode);
    FilterMode GetFilterMode() const noexcept;
    WrapMode GetWrapMode() const noexcept;
    const I32Extent2D& GetSize() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;
    
private:
    void Destroy();
    void UpdateTexParemeters();
    
/**@section Variable */
protected:
    bool m_isUseMipmap;
    bool m_isDynamicUsage;
    PixelFormat m_pixelFormat;
    FilterMode m_filterMode;
    WrapMode m_wrapMode;
    I32Extent2D m_size;
};
    
} /* namespace tgon */
