#include "PrecompiledHeader.h"

#include "Core/Algorithm.h"

#include "OpenGLTexture.h"
#include "OpenGLDebug.h"

namespace tgon
{

constexpr bool g_isUsePixelBuffer = false;
    
constexpr GLint ConvertTextureFilterModeToNative(FilterMode textureFilterMode) noexcept
{
    constexpr GLint nativeTextureFilterModes[] = {
        GL_NEAREST,         // Point,
        GL_LINEAR           // Bilinear,
    };
    return nativeTextureFilterModes[static_cast<int>(textureFilterMode)];
}
    
constexpr GLint ConvertTextureWrapModeToNative(WrapMode textureWrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModes[] = {
        GL_REPEAT,          // Repeat
        GL_CLAMP,           // Clamp
        GL_MIRRORED_REPEAT, // Mirror
    };
    return nativeTextureWrapModes[static_cast<int>(textureWrapMode)];
}

constexpr GLint ConvertPixelFormatToNative(PixelFormat pixelFormat) noexcept
{
    constexpr GLint nativePixelFormats[] = {
        -1,                 // Unknown
        GL_RGBA,            // RGBA8888
        GL_RGB,             // RGB888
        GL_RGB4,            // RGBA4444
        GL_RED,             // R8
    };              
    return nativePixelFormats[static_cast<int>(pixelFormat)];
}

OpenGLTexture::OpenGLTexture(const std::string_view& filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    OpenGLTexture(Image(filePath), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

OpenGLTexture::OpenGLTexture(Image&& image, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    OpenGLTexture(image.GetImageData().get(), image.GetSize(), image.GetPixelFormat(), filterMode, wrapMode, isUseMipmap, isDynamicUsage)
{
}

OpenGLTexture::OpenGLTexture(const uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    m_isUseMipmap(isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_pixelBufferHandle(this->CreatePixelBufferHandle(size.width * size.height * GetBytesPerPixel(pixelFormat))),
    m_pixelFormat(pixelFormat),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_size(size),
    m_isDynamicUsage(isDynamicUsage)
{
    assert(m_textureHandle != 0);
    
    this->SetData(imageData, size, pixelFormat);
    
    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

OpenGLTexture::~OpenGLTexture()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
    TGON_GL_ERROR_CHECK(glDeleteBuffers(1, &m_pixelBufferHandle));
    
    m_textureHandle = 0;
    m_pixelBufferHandle = 0;
}

void OpenGLTexture::Use()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));

    // Let the texture object to use pixel buffer
    if constexpr (g_isUsePixelBuffer)
    {
        TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pixelBufferHandle));
        auto nativePixelFormat = ConvertPixelFormatToNative(m_pixelFormat);
        glTexImage2D(GL_TEXTURE_2D, 0, nativePixelFormat, m_size.width, m_size.height, 0, nativePixelFormat, GL_UNSIGNED_BYTE, nullptr);
    }

    this->UpdateTexParemeters();
}
    
void OpenGLTexture::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLTexture::SetData(const uint8_t* imageData, const I32Extent2D& size, PixelFormat pixelFormat)
{
    auto nativePixelFormat = ConvertPixelFormatToNative(pixelFormat);
    if constexpr (g_isUsePixelBuffer)
    {
        // Set image data into pixel buffer
        TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pixelBufferHandle));
        TGON_GL_ERROR_CHECK(glBufferData(GL_PIXEL_UNPACK_BUFFER, size.width * size.height * GetBytesPerPixel(pixelFormat), nullptr, GL_STATIC_DRAW));
        uint8_t* pixelBufferPtr = TGON_GL_ERROR_CHECK(reinterpret_cast<uint8_t*>(glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY)));
        memcpy(pixelBufferPtr, imageData, size.width * size.height * GetBytesPerPixel(pixelFormat));
        TGON_GL_ERROR_CHECK(glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER));
    }
    else
    {
        TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
        TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, nativePixelFormat, size.width, size.height, 0, nativePixelFormat, GL_UNSIGNED_BYTE, imageData));
    }
}

void OpenGLTexture::SetData(const uint8_t* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat)
{
    auto nativePixelFormat = ConvertPixelFormatToNative(pixelFormat);
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, pos.x, pos.y, size.width, size.height, nativePixelFormat, GL_UNSIGNED_BYTE, imageData));
}

void OpenGLTexture::UpdateTexParemeters()
{
    // Update texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertTextureFilterModeToNative(m_filterMode))); // When minifying the image

    // Update texture wrap mode
    auto wrapMode = ConvertTextureWrapModeToNative(m_wrapMode);
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));
}

void OpenGLTexture::SetFilterMode(FilterMode filterMode)
{
    m_filterMode = filterMode;
}

void OpenGLTexture::SetWrapMode(WrapMode wrapMode)
{
    m_wrapMode = wrapMode;
}

GLuint OpenGLTexture::CreateTextureHandle() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

GLuint OpenGLTexture::CreatePixelBufferHandle(int32_t bufferBytes) const
{
    GLuint pixelBufferHandle;
    TGON_GL_ERROR_CHECK(glGenBuffers(1, &pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_PIXEL_UNPACK_BUFFER, static_cast<GLsizeiptr>(bufferBytes), nullptr, GL_STATIC_DRAW));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));

    return pixelBufferHandle;
}

FilterMode OpenGLTexture::GetFilterMode() const noexcept
{
    return m_filterMode;
}

WrapMode OpenGLTexture::GetWrapMode() const noexcept
{
    return m_wrapMode;
}

void OpenGLTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

GLuint OpenGLTexture::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}

const I32Extent2D& OpenGLTexture::GetSize() const noexcept
{
    return m_size;
}
    
} /* namespace tgon */
