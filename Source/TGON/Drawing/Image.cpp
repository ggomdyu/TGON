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
    m_imageData(nullptr)
{
}

Image::Image(Image&& rhs) noexcept :
    m_imageData(std::move(rhs.m_imageData)),
    m_filePath(std::move(rhs.m_filePath)),
    m_size(rhs.m_size)
{
    rhs.m_size = {};
}

Image& Image::operator=(Image&& rhs)
{
    m_imageData = std::move(rhs.m_imageData);
    m_filePath = std::move(rhs.m_filePath);
    m_size = rhs.m_size;

    rhs.m_size = {};

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

const I32Extent2D& Image::GetSize() const noexcept
{
    return m_size;
}

int32_t Image::GetChannels() const noexcept
{
    return 4;
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
    return stbi_write_png(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get(), m_size.width * 4) != 0;
}

bool Image::SaveAsJpeg(const char* saveFilePath, int32_t quality)
{
    return stbi_write_jpg(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get(), quality) != 0;
}

bool Image::SaveAsBmp(const char* saveFilePath)
{
    return stbi_write_bmp(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get()) != 0;
}

bool Image::SaveAsTga(const char* saveFilePath)
{
    return stbi_write_tga(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get()) != 0;
}

} /* namespace tgon */
