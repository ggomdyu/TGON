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
    m_image(filePath),
    m_isUseMipmap(isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode)
{
    assert(m_textureHandle != 0);
    
    this->TransferToVideo();
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

void OpenGLTexture::TransferToVideo()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.GetWidth(), m_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.GetImageData()));

    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void OpenGLTexture::UpdateTexParemeters()
{
    // Update texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertTextureFilterModeToNative(m_filterMode))); // When minifying the image

    // Update texture wrap mode
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertTextureWrapModeToNative(m_wrapMode)));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertTextureWrapModeToNative(m_wrapMode)));
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
    
bool OpenGLTexture::IsValid() const noexcept
{
    return m_image.IsValid();
}

int32_t OpenGLTexture::GetWidth() const noexcept
{
    return m_image.GetWidth();
}

int32_t OpenGLTexture::GetHeight() const noexcept
{
    return m_image.GetHeight();
}

I32Extent2D OpenGLTexture::GetSize() const noexcept
{
    return m_image.GetSize();
}

int32_t OpenGLTexture::GetChannels() const noexcept
{
    return m_image.GetChannels();
}

PixelFormat OpenGLTexture::GetPixelFormat() const noexcept
{
    return m_image.GetPixelFormat();
}
    
} /* namespace tgon */
