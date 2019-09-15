#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>
#include <stb_image_write.h>

#include "String/StringTraits.h"
#include "String/Hash.h"
#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
#   include "ImageProcessor/BmpImageProcessor.h"
#   include "ImageProcessor/JpgImageProcessor.h"
#   include "ImageProcessor/PngImageProcessor.h"
#endif
//#include "ImageProcessor/WebPImageProcessor.h"

#include "Image.h"

namespace tgon
{
namespace
{

TGON_API std::unique_ptr<std::byte[]> LoadImageData(const std::byte* fileData, int32_t fileDataBytes, int32_t* destWidth, int32_t* destHeight, PixelFormat* destPixelFormat)
{
#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
    auto loadImage = [&](auto& imageProcessor)
    {
        *destWidth = imageProcessor.GetWidth();
        *destHeight = imageProcessor.GetHeight();
        *destChannels = imageProcessor.GetChannels();
        
        return std::move(imageProcessor.GetImageData());
    };
    
    if (PngImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(PngImageProcessor(fileData, fileDataBytes));
    }
    else if (JpgImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(JpgImageProcessor(fileData, fileDataBytes));
    }
    else if (BmpImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(BmpImageProcessor(fileData, fileDataBytes));
    }
#else
    *destPixelFormat = PixelFormat::RGBA8888;
#endif
    
    return std::unique_ptr<std::byte[]>(reinterpret_cast<std::byte*>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(fileData), fileDataBytes, destWidth, destHeight, nullptr, STBI_rgb_alpha)));
}

TGON_API std::unique_ptr<std::byte[]> LoadImageData(const char* filePath, int32_t* destWidth, int32_t* destHeight, PixelFormat* destPixelFormat)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
#else
    FILE* file = fopen(filePath, "rb");
#endif
    if (file == nullptr)
    {
        return nullptr;
    }
    
    fseek(file, 0, SEEK_END);
    int32_t fileSize = static_cast<int32_t>(ftell(file));
    fseek(file, 0, SEEK_SET);
    
    auto fileData = std::make_unique<std::byte[]>(fileSize);
    fread(fileData.get(), 1, fileSize, file);
    fclose(file);
    
    return LoadImageData(fileData.get(), fileSize, destWidth, destHeight, destPixelFormat);
}

TGON_API ImageFormat ConvertStringToImageFormat(const std::string_view& str)
{
    char lowercaseStr[32] {};
    BasicStringTraits<char>::ToLower(str.data(), str.length(), lowercaseStr);
    
    switch (X65599Hash(lowercaseStr))
    {
        case TGON_X65599("bmp"):
            return ImageFormat::Bmp;
        case TGON_X65599("jpg"):
            return ImageFormat::Jpg;
        case TGON_X65599("jpeg"):
            return ImageFormat::Jpeg;
        case TGON_X65599("png"):
            return ImageFormat::Png;
        case TGON_X65599("tiff"):
            return ImageFormat::Tiff;
        case TGON_X65599("gif"):
            return ImageFormat::Gif;
        case TGON_X65599("webp"):
            return ImageFormat::WebP;
        default:
            return ImageFormat::Unknown;
    }
}

} /* namespace */

Image::Image() noexcept :
    m_imageData(nullptr),
    m_size(),
    m_pixelFormat(PixelFormat::Unknown)
{
}

Image::Image(const std::string_view& filePath) :
    Image()
{
    m_imageData = LoadImageData(filePath.data(), &m_size.width, &m_size.height, &m_pixelFormat);
}

Image::Image(const std::byte* fileData, int32_t fileDataBytes) :
    Image()
{
    m_imageData = LoadImageData(fileData, fileDataBytes, &m_size.width, &m_size.height, &m_pixelFormat);
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

std::byte& Image::operator[](std::size_t index)
{
    return m_imageData.get()[index];
}

std::byte Image::operator[](std::size_t index) const
{
    return m_imageData.get()[index];
}

bool Image::IsValid() const noexcept
{
    return m_imageData != nullptr;
}

void Image::SetImageData(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat)
{
    m_imageData.reset(imageData);
    m_size = size;
    m_pixelFormat = pixelFormat;
}

std::unique_ptr<std::byte[]>& Image::GetImageData() noexcept
{
    return m_imageData;
}

const std::unique_ptr<std::byte[]>& Image::GetImageData() const noexcept
{
    return m_imageData;
}

const I32Extent2D& Image::GetSize() const noexcept
{
    return m_size;
}

int32_t Image::GetChannels() const noexcept
{
    return ConvertPixelFormatToBytesPerPixel(m_pixelFormat);
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

ImageView::ImageView(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat) :
    m_imageData(imageData),
    m_size(size),
    m_pixelFormat(pixelFormat)
{
}

ImageView::ImageView(Image& image) :
    m_imageData(image.GetImageData().get()),
    m_size(image.GetSize()),
    m_pixelFormat(image.GetPixelFormat())
{
}

std::byte& ImageView::operator[](std::size_t index)
{
    return m_imageData[index];
}

const std::byte ImageView::operator[](std::size_t index) const
{
    return m_imageData[index];
}

std::byte* ImageView::GetImageData() noexcept
{
    return m_imageData;
}

const std::byte* ImageView::GetImageData() const noexcept
{
    return m_imageData;
}

const I32Extent2D& ImageView::GetSize() const noexcept
{
    return m_size;
}

int32_t ImageView::GetChannels() const noexcept
{
    return ConvertPixelFormatToBytesPerPixel(m_pixelFormat);
}

PixelFormat ImageView::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

} /* namespace tgon */
