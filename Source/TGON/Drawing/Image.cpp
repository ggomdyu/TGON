#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image_write.h>

#include "String/StringTraits.h"
#include "String/Hash.h"

#include "Image.h"

namespace tgon
{

Image::Image() noexcept :
    m_imageData(nullptr),
    m_width(0),
    m_height(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

Image::Image(Image&& rhs) noexcept :
    m_imageData(std::move(rhs.m_imageData)),
    m_filePath(std::move(rhs.m_filePath)),
    m_width(rhs.m_width),
    m_height(rhs.m_height),
    m_channels(rhs.m_channels)
{
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;
}

Image& Image::operator=(Image&& rhs)
{
    m_imageData = std::move(rhs.m_imageData);
    m_filePath = std::move(rhs.m_filePath);
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_channels = rhs.m_channels;

    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;

    return *this;
}

uint8_t& Image::operator[](std::size_t index)
{
    return m_imageData.get()[index];
}

const uint8_t Image::operator[](std::size_t index) const
{
    return m_imageData.get()[index];
}

bool Image::IsValid() const noexcept
{
    return m_imageData != nullptr;
}

std::unique_ptr<uint8_t[]>& Image::GetImageData() noexcept
{
    return m_imageData;
}

const std::unique_ptr<uint8_t[]>& Image::GetImageData() const noexcept
{
    return m_imageData;
}

int32_t Image::GetWidth() const noexcept
{
    return m_width;
}

int32_t Image::GetHeight() const noexcept
{
    return m_height;
}
    
I32Extent2D Image::GetSize() const noexcept
{
    return {m_width, m_height};
}

int32_t Image::GetChannels() const noexcept
{
    return m_channels;
}

PixelFormat Image::GetPixelFormat() const noexcept
{
    return PixelFormat::RGBA8888;
}

const StringHash& Image::GetFilePath() const noexcept
{
    return m_filePath;
}

bool Image::SaveAsPng(const char* saveFilePath)
{
    return stbi_write_png(saveFilePath, m_width, m_height, 4, m_imageData.get(), m_width * 4) != 0;
}

bool Image::SaveAsJpeg(const char* saveFilePath, int32_t quality)
{
    return stbi_write_jpg(saveFilePath, m_width, m_height, 4, m_imageData.get(), quality) != 0;
}

bool Image::SaveAsBmp(const char* saveFilePath)
{
    return stbi_write_bmp(saveFilePath, m_width, m_height, 4, m_imageData.get()) != 0;
}

bool Image::SaveAsTga(const char* saveFilePath)
{
    return stbi_write_tga(saveFilePath, m_width, m_height, 4, m_imageData.get()) != 0;
}

} /* namespace tgon */
