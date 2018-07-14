#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "OpenGLTexture.h"
#include "OpenGLUtility.h"
#include "../TextureType.h"

namespace tgon
{

TextureImpl::TextureImpl(const std::string& filePath, const TextureProperty& textureProperty) :
    Image(filePath),
    m_isUseMipmap(textureProperty.isUseMipmap),
    m_textureHandle(this->CreateTextureHandle()),
    m_filterMode(static_cast<GLint>(textureProperty.filterMode)),
    m_wrapMode(static_cast<GLint>(textureProperty.wrapMode))
{
    assert(m_textureHandle != 0);
}

TextureImpl::~TextureImpl()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
}

void TextureImpl::Use()
{
    this->TransferToVideo();
    this->UpdateParemeters();
}

void TextureImpl::TransferToVideo()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->GetWidth(), this->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->GetImageData().get()));

    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void TextureImpl::UpdateParemeters()
{
    // Update texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode)); // When minifying the image

    // Update texture wrap mode
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode));
}

void TextureImpl::SetFilterMode(TextureFilterMode filterMode)
{
    m_filterMode = static_cast<GLint>(filterMode);
}

void TextureImpl::SetWrapMode(TextureWrapMode wrapMode)
{
    m_wrapMode = static_cast<GLint>(wrapMode);
}

GLuint TextureImpl::CreateTextureHandle() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

TextureFilterMode TextureImpl::GetFilterMode() const noexcept
{
    return static_cast<TextureFilterMode>(m_filterMode);
}

TextureWrapMode TextureImpl::GetWrapMode() const noexcept
{
    return static_cast<TextureWrapMode>(m_wrapMode);
}

void TextureImpl::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

bool TextureImpl::IsValid() const noexcept
{
    return Image::IsValid();
}
    
std::unique_ptr<uint8_t[]>& TextureImpl::GetImageData() noexcept
{
    return Image::GetImageData();
}
    
const std::unique_ptr<uint8_t[]>& TextureImpl::GetImageData() const noexcept
{
    return Image::GetImageData();
}
    
int32_t TextureImpl::GetWidth() const noexcept
{
    return Image::GetWidth();
}
    
int32_t TextureImpl::GetHeight() const noexcept
{
    return Image::GetHeight();
}
    
int32_t TextureImpl::GetChannels() const noexcept
{
    return Image::GetChannels();
}
    
int32_t TextureImpl::GetColorDepth() const noexcept
{
    return Image::GetColorDepth();
}
    
PixelFormat TextureImpl::GetPixelFormat() const noexcept
{
    return Image::GetPixelFormat();
}
    
const std::string& TextureImpl::GetFilePath() const noexcept
{
    return Image::GetFilePath();
}
    
GLuint TextureImpl::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}
    
} /* namespace tgon */
