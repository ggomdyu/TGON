#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "OpenGLFontTexture.h"
#include "OpenGLDebug.h"

namespace tgon
{

OpenGLFontTexture::OpenGLFontTexture(const char* filePath, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap) :
    m_image(filePath),
    m_isUseMipmap(isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode)
{
    assert(m_textureHandle != 0);
    
    this->TransferToVideo();
}

OpenGLFontTexture::~OpenGLFontTexture()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
    m_textureHandle = 0;
}

void OpenGLFontTexture::Use()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    
    this->UpdateTexParemeters();
}
    
void OpenGLFontTexture::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLFontTexture::TransferToVideo()
{
    /*TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.GetWidth(), m_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.GetImageData()));
*/
    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void OpenGLFontTexture::UpdateTexParemeters()
{
    // Update texture filter
    //TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    //TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertTextureFilterModeToNative(m_filterMode))); // When minifying the image
    //
    //// Update texture wrap mode
    //TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, ConvertTextureWrapModeToNative(m_wrapMode)));
    //TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, ConvertTextureWrapModeToNative(m_wrapMode)));
}

void OpenGLFontTexture::SetFilterMode(FilterMode filterMode)
{
    m_filterMode = filterMode;
}

void OpenGLFontTexture::SetWrapMode(WrapMode wrapMode)
{
    m_wrapMode = wrapMode;
}

GLuint OpenGLFontTexture::CreateTextureHandle() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

FilterMode OpenGLFontTexture::GetFilterMode() const noexcept
{
    return m_filterMode;
}

WrapMode OpenGLFontTexture::GetWrapMode() const noexcept
{
    return m_wrapMode;
}

void OpenGLFontTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

GLuint OpenGLFontTexture::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}
    
bool OpenGLFontTexture::IsValid() const noexcept
{
    return m_image.IsValid();
}

I32Extent2D OpenGLFontTexture::GetSize() const noexcept
{
    return m_image.GetSize();
}

int32_t OpenGLFontTexture::GetChannels() const noexcept
{
    return m_image.GetChannels();
}

PixelFormat OpenGLFontTexture::GetPixelFormat() const noexcept
{
    return m_image.GetPixelFormat();
}
    
} /* namespace tgon */
