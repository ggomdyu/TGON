#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>
#include <stb_image_write.h>

#include "IO/File.h"
#include "Core/Algorithm.h"
#if TGON_USING_SIMD
#include "Core/Simd.h"
#endif

#include "Image.h"

namespace tg
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

template <int32_t _BytesPerPixel>
void FlipImageX(std::byte* imageData, int32_t width, int32_t height)
{
#if TGON_USING_SIMD
#else
    using ColorRef = struct { std::byte _[4]; }*;

    auto frontRow = reinterpret_cast<ColorRef>(imageData);
    auto backRow = &(reinterpret_cast<ColorRef>(imageData))[width - 1];

    for (; frontRow < backRow; ++frontRow, --backRow)
    {
        for (int32_t col = 0; col < width * height; col += width)
        {
            std::swap(*(frontRow + col), *(backRow + col));
        }
    }
#endif
}

template <int32_t _BytesPerPixel>
void FlipImageXY(std::byte* imageData, int32_t width, int32_t height)
{
#if TGON_USING_SIMD
#else
    using ColorRef = struct { std::byte _[_BytesPerPixel]; }*;

    auto* frontRow = reinterpret_cast<ColorRef>(imageData);
    auto* backRow = &(reinterpret_cast<ColorRef>(imageData))[width * height - 1];

    for (; frontRow < backRow; ++frontRow, --backRow)
    {
        std::swap(*frontRow, *backRow);
    }
#endif
}

void FlipImageY(std::byte* imageData, int32_t width, int32_t height, int32_t bytesPerPixel)
{
#if TGON_USING_SIMD
#else
    const size_t stride = width * bytesPerPixel;
    const auto tempRowBuffer = std::make_unique<std::byte[]>(stride);

    auto* frontRow = imageData;
    auto* backRow = &imageData[(height - 1) * stride];

    for (; frontRow < backRow; frontRow += stride, backRow -= stride)
    {
        std::copy_n(frontRow, stride, tempRowBuffer.get());
        std::copy_n(backRow, stride, frontRow);
        std::copy_n(tempRowBuffer.get(), stride, backRow);
    }
#endif
}
template <int32_t _BytesPerPixel>
void RotateImageRight90Degrees(std::byte* imageData, int32_t width, int32_t height)
{
#if TGON_USING_SIMD
#else
    using ColorRef = struct { std::byte _[_BytesPerPixel]; }*;
    const auto imageDataSize = static_cast<int64_t>(width) * height * _BytesPerPixel;
    const auto tempBuffer = std::make_unique<std::byte[]>(imageDataSize);

    auto* srcRow = reinterpret_cast<ColorRef>(imageData);
    auto* destCol = &(reinterpret_cast<ColorRef>(tempBuffer.get()))[height - 1];

    for (; srcRow < reinterpret_cast<ColorRef>(imageData) + width * height; srcRow += width, --destCol)
    {
        for (int32_t x = 0; x < width; ++x)
        {
            destCol[x * height] = srcRow[x];
        }
    }

    std::copy_n(tempBuffer.get(), imageDataSize, imageData);
#endif
}

template <int32_t _BytesPerPixel>
void RotateImageLeft90Degrees(std::byte* imageData, int32_t width, int32_t height)
{
#if TGON_USING_SIMD
#else
    using ColorRef = struct { std::byte _[_BytesPerPixel]; }*;
    const auto imageDataSize = static_cast<int64_t>(width) * height * _BytesPerPixel;
    const auto tempBuffer = std::make_unique<std::byte[]>(imageDataSize);

    auto* srcRow = reinterpret_cast<ColorRef>(imageData);
    auto* destCol = &reinterpret_cast<ColorRef>(tempBuffer.get())[(width - 1) * height];

    for (; srcRow < reinterpret_cast<ColorRef>(imageData) + width * height; srcRow += width, ++destCol)
    {
        for (int32_t x = 0; x < width; ++x)
        {
            destCol[-x * height] = srcRow[x];
        }
    }

    std::copy_n(tempBuffer.get(), imageDataSize, imageData);
#endif
}

}

Image::Image(std::unique_ptr<std::byte[]> imageData, const I32Extent2D& size, PixelFormat pixelFormat) :
    m_imageData(std::move(imageData)),
    m_size(size)
{
}

bool Image::operator==(std::nullptr_t rhs) const noexcept
{
    return m_imageData == nullptr;
}

bool Image::operator!=(std::nullptr_t rhs) const noexcept
{
    return m_imageData != nullptr;
}

std::byte& Image::operator[](int32_t index) noexcept
{
    return m_imageData[index];
}

std::byte Image::operator[](int32_t index) const noexcept
{
    return m_imageData[index];
}

std::optional<Image> Image::FromFile(const char8_t* filePath)
{
    auto fileData = File::ReadAllBytes(filePath, ReturnVectorTag{});
    if (fileData.has_value() == false)
    {
        return {};
    }

    return FromBytes(*fileData);
}

std::optional<Image> Image::FromBytes(const std::span<const std::byte>& bytes)
{
    int width = 0, height = 0;
    auto imageData = std::unique_ptr<std::byte[]>(reinterpret_cast<std::byte*>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(&bytes[0]), static_cast<int>(bytes.size()), &width, &height, nullptr, STBI_rgb_alpha)));
    if (imageData == nullptr)
    {
        return {};
    }

    return Image(std::move(imageData), {static_cast<int32_t>(width), static_cast<int32_t>(height)}, PixelFormat::RGBA8888);
}

std::byte* Image::GetImageData() noexcept
{
    return &m_imageData[0];
}

const std::byte* Image::GetImageData() const noexcept
{
    return &m_imageData[0];
}

int32_t Image::GetWidth() const noexcept
{
    return m_size.width;
}

int32_t Image::GetHeight() const noexcept
{
    return m_size.height;
}

const I32Extent2D& Image::GetSize() const noexcept
{
    return m_size;
}

PixelFormat Image::GetPixelFormat() const noexcept
{
    return InternalPixelFormat;
}

bool Image::Save(const char8_t* filePath, ImageFormat format) const
{
    switch (format)
    {
    case ImageFormat::Png:
        return stbi_write_png(reinterpret_cast<const char*>(filePath), m_size.width, m_size.height, 4, m_imageData.get(), m_size.width * 4) != 0;

    case ImageFormat::Jpeg:
        return stbi_write_jpg(reinterpret_cast<const char*>(filePath), m_size.width, m_size.height, 4, m_imageData.get(), 100) != 0;

    case ImageFormat::Bmp:
        return stbi_write_bmp(reinterpret_cast<const char*>(filePath), m_size.width, m_size.height, 4, m_imageData.get()) != 0;

    default:
        return false;
    }
}

void Image::RotateFlip(RotateFlipType rotateFlipType)
{
    static_assert(InternalPixelFormat == PixelFormat::RGBA8888, "Image::RotateFlip only supports RGBA8888 format.");

    constexpr auto BytesPerPixel = ConvertPixelFormatToChannelCount(InternalPixelFormat);

    switch (rotateFlipType)
    {
    case RotateFlipType::RotateNoneFlipNone:
        break;

    case RotateFlipType::Rotate90FlipNone:
        RotateImageRight90Degrees<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        std::swap(m_size.width, m_size.height);
        break;

    case RotateFlipType::Rotate180FlipNone:
        FlipImageXY<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        break;

    case RotateFlipType::Rotate270FlipNone:
        RotateImageLeft90Degrees<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        std::swap(m_size.width, m_size.height);
        break;

    case RotateFlipType::RotateNoneFlipX:
        FlipImageX<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        break;

    case RotateFlipType::Rotate90FlipX:
        RotateImageRight90Degrees<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        FlipImageX<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        std::swap(m_size.width, m_size.height);
        break;

    case RotateFlipType::RotateNoneFlipY:
        FlipImageY(m_imageData.get(), m_size.width, m_size.height, BytesPerPixel);
        break;

    case RotateFlipType::Rotate90FlipY:
        RotateImageRight90Degrees<BytesPerPixel>(m_imageData.get(), m_size.width, m_size.height);
        FlipImageY(m_imageData.get(), m_size.width, m_size.height, BytesPerPixel);
        std::swap(m_size.width, m_size.height);
        break;
    }
}

}
