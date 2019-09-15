/**
 * @file    OpenGLTexture.h
 * @author  ggomdyu
 * @since   02/20/2018
 */

#pragma once
#include <GL/glew.h>

#include "Core/NonCopyable.h"
#include "Drawing/Image.h"
#include "Math/Vector2.h"

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

class TGON_API OpenGLTexture :
    private NonCopyable
{
/**@section Constructor */
public:
    OpenGLTexture(const std::string_view& filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    OpenGLTexture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);
    OpenGLTexture(Image&& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage);

/**@section Destructor */
public:
    ~OpenGLTexture();

/**@section Method */
public:
    void Use();
    void Unuse();
    bool IsValid() const;
    void SetData(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetData(const std::byte* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat);
    void SetFilterMode(FilterMode filterMode);
    void SetWrapMode(WrapMode wrapMode);
    FilterMode GetFilterMode() const noexcept;
    WrapMode GetWrapMode() const noexcept;
    GLuint GetTextureHandle() const noexcept;
    const I32Extent2D& GetSize() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;
    
private:
    void UpdateTexParemeters();
    GLuint CreateTextureHandle() const;
    GLuint CreatePixelBufferHandle(int32_t bufferBytes) const;
    void CreateMipmap() const;

private:
    bool m_isUseMipmap;
    bool m_isDynamicUsage;
    GLuint m_textureHandle;
    GLuint m_pixelBufferHandle;
    PixelFormat m_pixelFormat;
    FilterMode m_filterMode;
    WrapMode m_wrapMode;
    I32Extent2D m_size;
};

using PlatformTexture = OpenGLTexture;

} /* namespace tgon */
