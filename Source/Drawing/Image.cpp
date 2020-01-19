#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>
#include <stb_image_write.h>

#include "IO/File.h"
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

Image::Image(std::unique_ptr<std::byte[]>&& imageData, const I32Extent2D& size, PixelFormat pixelFormat) :
    m_imageData(std::move(imageData)),
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

bool Image::operator==(const Image& rhs) const noexcept
{
    return m_size == rhs.m_size && m_pixelFormat == rhs.m_pixelFormat && memcmp(&m_imageData[0], &rhs.m_imageData[0], m_size.width * m_size.height * ConvertPixelFormatToChannelCount(m_pixelFormat)) == 0;
}

bool Image::operator!=(const Image& rhs) const noexcept
{
    return !this->operator==(rhs);
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

std::optional<Image> Image::Create(const char* filePath)
{
    auto fileData = File::ReadAllBytes(filePath, ReturnVectorTag{});
    if (fileData.has_value() == false)
    {
        return {};
    }

    return Create(*fileData);
}

std::optional<Image> Image::Create(const gsl::span<const std::byte>& fileData)
{
    int width = 0, height = 0;
    auto imageData = std::unique_ptr<std::byte[]>(reinterpret_cast<std::byte*>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(&fileData[0]), static_cast<int>(fileData.size()), &width, &height, nullptr, STBI_rgb_alpha)));
    if (imageData == nullptr)
    {
        return {};
    }

    return Image(std::move(imageData), {static_cast<int32_t>(width), static_cast<int32_t>(height)}, PixelFormat::RGBA8888);
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

} /* namespace tgon */
