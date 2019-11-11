#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>
#include <stb_image_write.h>

#include "Text/StringTraits.h"
#include "Text/Hash.h"
#include "Misc/Algorithm.h"

#include "Image.h"

namespace tgon
{
namespace
{

constexpr int32_t ConvertPixelFormatToChannelCount(PixelFormat pixelFormat)
{
    constexpr int32_t channelCountTable[] = {
        0, // Unknown
        4, // RGBA8888
        3, // RGB888
        4, // RGBA4444
        1, // R8
    };
    
    return channelCountTable[UnderlyingCast(pixelFormat)];
}

} /* namespace */

Image::Image(const char* filePath) :
    Image()
{
    this->LoadImageData(filePath);
}

Image::Image(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat) :
    m_imageData(imageData),
    m_size(size),
    m_pixelFormat(pixelFormat)
{
}

Image::Image(Image&& rhs) noexcept :
    m_imageData(std::move(rhs.m_imageData)),
    m_size(rhs.m_size),
    m_pixelFormat(rhs.m_pixelFormat)
{
    rhs.m_size = {};
    rhs.m_pixelFormat = PixelFormat::Unknown;
}

Image& Image::operator=(Image&& rhs) noexcept
{
    m_imageData = std::move(rhs.m_imageData);
    m_size = rhs.m_size;
    m_pixelFormat = rhs.m_pixelFormat;

    rhs.m_size = {};
    rhs.m_pixelFormat = PixelFormat::Unknown;

    return *this;
}

std::byte& Image::operator[](size_t index) noexcept
{
    return m_imageData[index];
}

std::byte Image::operator[](size_t index) const noexcept
{
    return m_imageData[index];
}

void Image::SetData(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat)
{
    m_imageData.reset(imageData);
    m_size = size;
    m_pixelFormat = pixelFormat;
}

std::byte* Image::GetData() noexcept
{
    return &m_imageData[0];
}

const std::byte* Image::GetData() const noexcept
{
    return &m_imageData[0];
}

const I32Extent2D& Image::GetSize() const noexcept
{
    return m_size;
}

int32_t Image::GetChannels() const noexcept
{
    return ConvertPixelFormatToChannelCount(m_pixelFormat);
}

PixelFormat Image::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

bool Image::SaveAsPng(const char* saveFilePath) const
{
    return stbi_write_png(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get(), m_size.width * 4) != 0;
}

bool Image::SaveAsJpeg(const char* saveFilePath, int32_t quality) const
{
    return stbi_write_jpg(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get(), quality) != 0;
}

bool Image::SaveAsBmp(const char* saveFilePath) const
{
    return stbi_write_bmp(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get()) != 0;
}

bool Image::SaveAsTga(const char* saveFilePath) const
{
    return stbi_write_tga(saveFilePath, m_size.width, m_size.height, 4, m_imageData.get()) != 0;
}

void Image::LoadImageData(const std::byte* fileData, int32_t fileDataBytes)
{
    int width = 0, height = 0;
    m_imageData = std::unique_ptr<std::byte[]>(reinterpret_cast<std::byte*>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(fileData), fileDataBytes, &width, &height, nullptr, STBI_rgb_alpha)));
    m_size = {static_cast<decltype(m_size.width)>(width), static_cast<decltype(m_size.height)>(height)};
}

void Image::LoadImageData(const char* filePath)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
#else
    FILE* file = fopen(filePath, "rb");
#endif
    if (file == nullptr)
    {
        return;
    }
    
    fseek(file, 0, SEEK_END);
    auto fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    auto fileData = std::make_unique<std::byte[]>(static_cast<size_t>(fileSize));
    fread(&fileData[0], 1, fileSize, file);
    fclose(file);
    
    this->LoadImageData(&fileData[0], static_cast<int32_t>(fileSize));
}

} /* namespace tgon */
