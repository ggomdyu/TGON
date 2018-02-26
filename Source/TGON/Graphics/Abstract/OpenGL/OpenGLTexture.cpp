#include "PrecompiledHeader.pch"

#include "OpenGLTexture.h"

#include <type_traits>
#include <cassert>

namespace tgon
{
namespace graphics
{

constexpr GLint ConvertTextureFillModeToNative(TextureFilterMode fillMode) noexcept
{
    constexpr GLint nativeVertexFormatTypeTable[] =
    {
        GL_NEAREST,
        GL_POINT,
    };

    return nativeVertexFormatTypeTable[static_cast<std::underlying_type_t<TextureFilterMode>>(fillMode)];
}

constexpr TextureFilterMode ConvertNativeToFilterMode(GLint fillMode)
{
    return static_cast<TextureFilterMode>(fillMode);
};

OpenGLTexture::OpenGLTexture(const std::string& filePath) :
    GenericTexture(filePath),
    m_rawFilterMode(GL_LINEAR)
{
    glGenTextures(1, &m_rawTextureHandle);

    assert(m_rawTextureHandle != 0);
}

void OpenGLTexture::Use()
{
    glBindTexture(GL_TEXTURE_2D, m_rawTextureHandle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, GetBits().data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_rawFilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_rawFilterMode);
}

[[deprecated]]
void OpenGLTexture::Unuse()
{
}

void OpenGLTexture::SetFilterMode(TextureFilterMode filterMode)
{
    m_filterMode = filterMode;
    m_rawFilterMode = ConvertTextureFillModeToNative(filterMode);
}

void OpenGLTexture::SetAddressMode(TextureAddressMode addressMode)
{
//    m_addressMode = addressMode;
//    m_rawAddressMode = ConvertTextureAddressModeToNative(addressMode);
}

} /* namespace graphics */
} /* namespace tgon */
