#include "PrecompiledHeader.h"

#include "Core/Platform/Config.h"

#include "Texture.h"
#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLTexture.h"
#endif

namespace tgon
{

Texture::Texture(const std::string& filePath, const TextureProperty& textureProperty) :
    m_textureImpl(std::make_unique<TextureImpl>(filePath, textureProperty))
{
}

Texture::~Texture() = default;

void Texture::Use()
{
    m_textureImpl->Use();
}

void Texture::SetFilterMode(TextureFilterMode filterMode)
{
    m_textureImpl->SetFilterMode(filterMode);
}
    
void Texture::SetWrapMode(TextureWrapMode wrapMode)
{
    m_textureImpl->SetWrapMode(wrapMode);
}
    
TextureFilterMode Texture::GetFilterMode() const noexcept
{
    return m_textureImpl->GetFilterMode();
}
    
TextureWrapMode Texture::GetWrapMode() const noexcept
{
    return m_textureImpl->GetWrapMode();
}
    
bool Texture::IsValid() const noexcept
{
    return m_textureImpl->IsValid();
}
    
std::vector<uint8_t>& Texture::GetImageData() noexcept
{
    return m_textureImpl->GetImageData();
}
    
const std::vector<uint8_t>& Texture::GetImageData() const noexcept
{
    return m_textureImpl->GetImageData();
}
    
int32_t Texture::GetWidth() const noexcept
{
    return m_textureImpl->GetWidth();
}
    
int32_t Texture::GetHeight() const noexcept
{
    return m_textureImpl->GetHeight();
}
    
int32_t Texture::GetChannels() const noexcept
{
    return m_textureImpl->GetChannels();
}
    
int32_t Texture::GetColorDepth() const noexcept
{
    return m_textureImpl->GetColorDepth();
}
    
PixelFormat Texture::GetPixelFormat() const noexcept
{
    return m_textureImpl->GetPixelFormat();
}
    
const std::string& Texture::GetFilePath() const noexcept
{
    return m_textureImpl->GetFilePath();
}

} /* namespace tgon */
