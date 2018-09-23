#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "OpenGLTexture.h"
#include "OpenGLUtility.h"

namespace tgon
{

OpenGLTexture::OpenGLTexture(const std::string& filePath, const TextureProperty& textureProperty) :
    Image(filePath),
    m_isUseMipmap(textureProperty.isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_filterMode(static_cast<GLint>(textureProperty.filterMode)),
    m_wrapMode(static_cast<GLint>(textureProperty.wrapMode))
{
    assert(m_textureHandle != 0);
    
    this->TransferToVideo();
}

OpenGLTexture::~OpenGLTexture()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
}

void OpenGLTexture::Use()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    
    this->UpdateTexParemeters();
}

void OpenGLTexture::TransferToVideo()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->GetWidth(), this->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->GetImageData()));

    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void OpenGLTexture::UpdateTexParemeters()
{
    // Update texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode)); // When minifying the image

    // Update texture wrap mode
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode));
}

void OpenGLTexture::SetFilterMode(TextureFilterMode filterMode)
{
    m_filterMode = static_cast<GLint>(filterMode);
}

void OpenGLTexture::SetWrapMode(TextureWrapMode wrapMode)
{
    m_wrapMode = static_cast<GLint>(wrapMode);
}

GLuint OpenGLTexture::CreateTextureHandle() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

TextureFilterMode OpenGLTexture::GetFilterMode() const noexcept
{
    return static_cast<TextureFilterMode>(m_filterMode);
}

TextureWrapMode OpenGLTexture::GetWrapMode() const noexcept
{
    return static_cast<TextureWrapMode>(m_wrapMode);
}

void OpenGLTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

GLuint OpenGLTexture::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}
    
} /* namespace tgon */
