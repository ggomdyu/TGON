/**
 * @file    Texture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include "Math/Vector2.h"
#include "Drawing/Image.h"

#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{

enum class FilterMode
{
    Point,
    Linear,
    Trilinear
};

enum class WrapMode
{
    Repeat,
    Clamp,
    Mirror,
};

class Texture final :
    private PlatformTexture
{
/**@section Constructor */
public:
    Texture(const Image& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    Texture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    Texture(Texture&& rhs) noexcept;

/**@section Operator */
public:
    Texture& operator=(Texture&& rhs) noexcept;
  
/**@section Method */
public:
    PlatformTexture& GetPlatformDependency() noexcept;
    const PlatformTexture& GetPlatformDependency() const noexcept;
    void Use();
    void Unuse();
    void SetData(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetData(const std::byte* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetFilterMode(FilterMode filterMode);
    void SetWrapMode(WrapMode wrapMode);
    const I32Extent2D& GetSize() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;
    FilterMode GetFilterMode() const noexcept;
    WrapMode GetWrapMode() const noexcept;
    void* GetNativeTexture() noexcept;
    const void* GetNativeTexture() const noexcept;
    bool IsValid() const;
    bool IsUseMipmap() const noexcept;
    
/**@section Variable */
protected:
    bool m_isUseMipmap = false;
    bool m_isDynamicUsage = false;
    PixelFormat m_pixelFormat = PixelFormat::RGBA8888;
    FilterMode m_filterMode = FilterMode::Linear;
    WrapMode m_wrapMode = WrapMode::Clamp;
    I32Extent2D m_size;
    inline static Texture* g_lastUsedTexture;
};
    
} /* namespace tgon */
