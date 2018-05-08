#include "PrecompiledHeader.pch"

#include <type_traits>
#include <cassert>

#include "Core/Utility/Algorithm.h"

#include "OpenGLTexture.h"
#include "OpenGLUtility.h"

namespace tgon
{

constexpr GLint ConvertTextureFilterModeToNative(TextureFilterMode filterMode, bool isUseMipmap) noexcept
{
    if (isUseMipmap)
    {
        constexpr GLint nativeTextureFilterModeTable[] =
        {
            GL_NEAREST_MIPMAP_LINEAR,
            GL_LINEAR_MIPMAP_LINEAR,
        };

        return nativeTextureFilterModeTable[UnderlyingCast(filterMode)];
    }
    else
    {
        constexpr GLint nativeTextureFilterModeTable[] =
        {
            GL_NEAREST,
            GL_LINEAR,
        };

        return nativeTextureFilterModeTable[UnderlyingCast(filterMode)];
    }
}

constexpr TextureFilterMode ConvertNativeToTextureFilterMode(GLint filterMode)
{
    switch (filterMode)
    {
    case GL_LINEAR:
    case GL_LINEAR_MIPMAP_LINEAR:
        return TextureFilterMode::Bilinear;

    case GL_NEAREST:
    case GL_NEAREST_MIPMAP_LINEAR:
        return TextureFilterMode::Point;

    default:
        return TextureFilterMode(0);
    }
};

constexpr GLint ConvertTextureWrapModeToNative(TextureWrapMode wrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModeTable[] =
    {
        GL_REPEAT,
        GL_CLAMP,
        GL_MIRRORED_REPEAT,
    };

    return nativeTextureWrapModeTable[UnderlyingCast(wrapMode)];
}

constexpr TextureWrapMode ConvertNativeToTextureWrapMode(GLint wrapMode) noexcept
{
    switch (wrapMode)
    {
    case GL_REPEAT:
        return TextureWrapMode::Repeat;

    case GL_CLAMP:
        return TextureWrapMode::Clamp;

    case GL_MIRRORED_REPEAT:
        return TextureWrapMode::Mirror;

    default:
        return TextureWrapMode(0);
    }
}

OpenGLTexture::OpenGLTexture(const std::string& filePath, const TextureCreateDesc& textureCreateDesc) :
    GenericTexture(filePath, textureCreateDesc),
    m_textureHandle(CreateTexture()),
    m_filterMode(ConvertTextureFilterModeToNative(textureCreateDesc.filterMode, textureCreateDesc.isUseMipmap)),
    m_wrapMode(ConvertTextureWrapModeToNative(textureCreateDesc.wrapMode))
{
    assert(m_textureHandle != 0);
}

OpenGLTexture::~OpenGLTexture()
{
    TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
}

void OpenGLTexture::Use()
{
    this->TransferToVideo();
    this->UpdateParemeters();
}

void OpenGLTexture::TransferToVideo()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GetImageData().data()));

    if (m_isUseMipmap == true)
    {
        this->CreateMipmap();
    }
}

void OpenGLTexture::UpdateParemeters()
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
    m_filterMode = ConvertTextureFilterModeToNative(filterMode, m_isUseMipmap);
}

void OpenGLTexture::SetWrapMode(TextureWrapMode addressMode)
{
    m_wrapMode = ConvertTextureWrapModeToNative(addressMode);
}

GLuint OpenGLTexture::CreateTexture() const
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

TextureFilterMode OpenGLTexture::GetFilterMode() const noexcept
{
    return ConvertNativeToTextureFilterMode(m_filterMode);
}

TextureWrapMode OpenGLTexture::GetWrapMode() const noexcept
{
    return ConvertNativeToTextureWrapMode(m_wrapMode);
}

void OpenGLTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

} /* namespace tgon */