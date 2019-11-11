#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include "Misc/Algorithm.h"

#include "OpenGLDebug.h"

#include "../Texture.h"

namespace tgon
{
namespace
{

static Texture* g_lastUsedTexture = nullptr;

constexpr GLint ConvertTextureFilterModeToNative(FilterMode textureFilterMode) noexcept
{
    constexpr GLint nativeTextureFilterModes[] = {
        GL_NEAREST,
        GL_LINEAR
    };
    return nativeTextureFilterModes[UnderlyingCast(textureFilterMode)];
}
    
constexpr GLint ConvertTextureWrapModeToNative(WrapMode textureWrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModes[] = {
        GL_REPEAT,
        GL_CLAMP,
        GL_MIRRORED_REPEAT,
    };
    return nativeTextureWrapModes[UnderlyingCast(textureWrapMode)];
}

constexpr GLenum ConvertPixelFormatToNative(PixelFormat pixelFormat) noexcept
{
    constexpr GLenum nativePixelFormats[] = {
        0,
        GL_RGBA,
        GL_RGB,
        GL_RGB4,
        GL_RED,
    };              
    return nativePixelFormats[UnderlyingCast(pixelFormat)];
}

GLuint CreateTextureHandle()
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

GLuint CreatePixelBufferHandle(int32_t bufferBytes)
{
    GLuint pixelBufferHandle = 0;

    TGON_GL_ERROR_CHECK(glGenBuffers(1, &pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_PIXEL_UNPACK_BUFFER, static_cast<GLsizeiptr>(bufferBytes), nullptr, GL_STATIC_DRAW));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));

    return pixelBufferHandle;
}

} /* namespace */

OpenGLTexture::OpenGLTexture(GLuint textureHandle) noexcept :
    m_textureHandle(textureHandle)
{
}

OpenGLTexture::OpenGLTexture(OpenGLTexture&& rhs) noexcept :
    m_textureHandle(rhs.m_textureHandle)
{
    rhs.m_textureHandle = 0;
}

OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& rhs) noexcept
{
    m_textureHandle = rhs.m_textureHandle;

    rhs.m_textureHandle = 0;

    return *this;
}

void OpenGLTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

GLuint OpenGLTexture::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}

Texture::Texture(const char* filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    Texture(Image(filePath), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

Texture::Texture(const Image& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    Texture(image.GetData(), image.GetSize(), image.GetPixelFormat(), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

Texture::Texture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    OpenGLTexture(CreateTextureHandle()),
    m_isUseMipmap(isUseMipmap),
    m_pixelFormat(pixelFormat),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_size(size),
    m_isDynamicUsage(isDynamicUsage)
{
    this->SetData(imageData, size, pixelFormat);
    
    if (isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void Texture::Use()
{
    if (g_lastUsedTexture == this)
    {
        return;
    }

    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    this->UpdateTextureParameters();

    g_lastUsedTexture = this;
}
    
void Texture::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

    g_lastUsedTexture = nullptr;
}

bool Texture::IsValid() const
{
    return glIsTexture(m_textureHandle);
}

void Texture::SetData(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat)
{
    auto nativePixelFormat = ConvertPixelFormatToNative(pixelFormat);
    
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, nativePixelFormat, size.width, size.height, 0, nativePixelFormat, GL_UNSIGNED_BYTE, imageData));
}

void Texture::SetData(const std::byte* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat)
{
    auto nativePixelFormat = ConvertPixelFormatToNative(pixelFormat);
    
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pos.x), static_cast<GLint>(pos.y), static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height), nativePixelFormat, GL_UNSIGNED_BYTE, imageData));
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

void Texture::Destroy()
{
    if (m_textureHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
        m_textureHandle = 0;
    }
}

void Texture::UpdateTextureParameters()
{
    // Update the texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertTextureFilterModeToNative(m_filterMode))); // When minifying the image

    // Update the texture wrap mode
    auto wrapMode = ConvertTextureWrapModeToNative(m_wrapMode);
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));
}

} /* namespace tgon */
#endif
