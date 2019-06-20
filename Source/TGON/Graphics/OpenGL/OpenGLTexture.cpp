#include "PrecompiledHeader.h"

#include "Core/Algorithm.h"

#include "OpenGLTexture.h"
#include "OpenGLDebug.h"

namespace tgon
{
    
constexpr GLint ConvertTextureFilterModeToNative(TextureFilterMode textureFilterMode) noexcept
{
    constexpr GLint nativeTextureFilterModes[] = {
        GL_NEAREST,
        GL_LINEAR
    };
    return nativeTextureFilterModes[static_cast<int>(textureFilterMode)];
}
    
constexpr GLint ConvertTextureWrapModeToNative(TextureWrapMode textureWrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModes[] = {
        GL_REPEAT,
        GL_CLAMP,
        GL_MIRRORED_REPEAT,
    };
    return nativeTextureWrapModes[static_cast<int>(textureWrapMode)];
}

OpenGLTexture::OpenGLTexture(const std::string& filePath, TextureFilterMode filterMode, TextureWrapMode wrapMode, bool isUseMipmap) :
    OpenGLTexture(Image(filePath), filterMode, wrapMode, isUseMipmap)
{
}

OpenGLTexture::OpenGLTexture(Image&& image, TextureFilterMode filterMode, TextureWrapMode wrapMode, bool isUseMipmap) :
    OpenGLTexture(image.GetImageData().get(), image.GetSize(), filterMode, wrapMode, isUseMipmap)
{
}
    
OpenGLTexture::OpenGLTexture(uint8_t* imageData, const I32Extent2D& size, TextureFilterMode filterMode, TextureWrapMode wrapMode, bool isUseMipmap) :
    m_isUseMipmap(isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_size(size)
{
    assert(m_textureHandle != 0);
    
    this->SetData(imageData);
    
    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

OpenGLTexture::~OpenGLTexture()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
    m_textureHandle = 0;
}

void OpenGLTexture::Use()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    
    this->UpdateTexParemeters();
}
    
void OpenGLTexture::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLTexture::SetData(void* imageData)
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData));
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

void OpenGLTexture::SetFilterMode(TextureFilterMode filterMode)
{
    m_filterMode = filterMode;
}

void OpenGLTexture::SetWrapMode(TextureWrapMode wrapMode)
{
    m_wrapMode = wrapMode;
}

GLuint OpenGLTexture::CreateTextureHandle() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

TextureFilterMode OpenGLTexture::GetFilterMode() const noexcept
{
    return m_filterMode;
}

TextureWrapMode OpenGLTexture::GetWrapMode() const noexcept
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

PixelFormat OpenGLTexture::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}
    
} /* namespace tgon */
