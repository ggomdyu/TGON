#include "PrecompiledHeader.pch"

#include "OpenGLTexture.h"

#include "Core/Utility/Enumerator.h"

#include <type_traits>
#include <cassert>

namespace tgon
{
namespace graphics
{

constexpr GLint ConvertTextureFilterModeToNative(TextureFilterMode filterMode) noexcept
{
    constexpr GLint nativeTextureFilterModeTable[] =
    {
        GL_NEAREST,
        GL_LINEAR,
    };

    return nativeTextureFilterModeTable[core::ToUnderlying(filterMode)];
}

constexpr TextureFilterMode ConvertNativeToTextureFilterMode(GLint filterMode)
{
    if (filterMode == GL_LINEAR)
    {
        return TextureFilterMode::Bilinear;
    }
    else if (filterMode == GL_NEAREST)
    {
        return TextureFilterMode::Point;
    }
    else
    {
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

    return nativeTextureWrapModeTable[core::ToUnderlying(wrapMode)];
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
    m_textureHandle(GenerateTexture()),
    m_filterMode(ConvertTextureFilterModeToNative(textureCreateDesc.filterMode)),
    m_wrapMode(ConvertTextureWrapModeToNative(textureCreateDesc.wrapMode))
{
    assert(m_textureHandle != 0);

    if (textureCreateDesc.isUseMipmap == true)
    {
        this->GenerateMipmap();
    }
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_textureHandle);
}

void OpenGLTexture::TransferToVideo()
{
    glBindTexture(GL_TEXTURE_2D, m_textureHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GetBits().data());
}

void OpenGLTexture::UpdateParemeters()
{
    // Update texture filter
    if (m_isUseMipmap)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    // Update texture wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
}

void OpenGLTexture::SetFilterMode(TextureFilterMode filterMode)
{
    m_filterMode = ConvertTextureFilterModeToNative(filterMode);
}

void OpenGLTexture::SetWrapMode(TextureWrapMode addressMode)
{
    m_wrapMode = ConvertTextureWrapModeToNative(addressMode);
}

GLuint OpenGLTexture::GenerateTexture() const
{
    GLuint textureHandle;
    glGenTextures(1, &textureHandle);

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

void OpenGLTexture::GenerateMipmap() const
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

} /* namespace graphics */
} /* namespace tgon */
