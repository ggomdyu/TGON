#include "PrecompiledHeader.pch"

#include "Core/Debug/Log.h"

#include "Image.h"
#include "ImageUtility.h"
#include "ImageProcessor/Png/PngImageProcessor.h"
#include "ImageProcessor/Jpg/JpgImageProcessor.h"
#include "ImageProcessor/Bmp/BmpImageProcessor.h"
#include "ImageProcessor/WebP/WebPImageProcessor.h"

namespace tgon
{

Image::Image() :
    m_width(0),
    m_height(0),
    m_channels(0),
    m_colorDepth(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

Image::Image(const std::string& filePath) :
    Image()
{
    this->Initialize(filePath);
}

Image::Image(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, ImageFormat imageFormat) :
    Image()
{
    this->Initialize(filePath, srcData, srcDataBytes, imageFormat);
}

Image::Image(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes) :
    Image()
{
    this->Initialize(filePath, srcData, srcDataBytes);
}

Image::Image(Image&& rhs) :
    m_imageData(std::move(rhs.m_imageData)),
    m_width(rhs.m_width),
    m_height(rhs.m_height),
    m_channels(rhs.m_channels),
    m_colorDepth(rhs.m_colorDepth),
    m_pixelFormat(rhs.m_pixelFormat),
    m_filePath(std::move(rhs.m_filePath))
{
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;
    rhs.m_colorDepth = 0;
    rhs.m_pixelFormat = PixelFormat::Unknown;
}

Image& Image::operator=(Image&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    m_imageData = std::move(rhs.m_imageData);
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_channels = rhs.m_channels;
    m_colorDepth = rhs.m_colorDepth;
    m_pixelFormat = rhs.m_pixelFormat;
    m_filePath = std::move(rhs.m_filePath);

    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;
    rhs.m_colorDepth = 0;
    rhs.m_pixelFormat = PixelFormat::Unknown;

    return *this;
}

uint8_t& Image::operator[](std::size_t index)
{
    return m_imageData[index];
}

const uint8_t& Image::operator[](std::size_t index) const
{
    return m_imageData[index];
}

bool Image::Initialize(const std::string& filePath)
{
    FILE* file = fopen(filePath.c_str(), "rb");
    if (file == nullptr)
    {
        return false;
    }

    // Read the image data from file.
    std::vector<uint8_t> imageData;
    {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        imageData.resize(fileSize);
        fread(imageData.data(), 1, fileSize, file);
    };
    fclose(file);

    std::size_t extensionOffset = filePath.rfind('.') + 1;
    this->Initialize(filePath, imageData.data(), imageData.size(), ConvertStringToImageFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset));
}

bool Image::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, ImageFormat imageFormat)
{
    m_filePath = filePath;

    switch (imageFormat)
    {
    case ImageFormat::Png:
        {
            PngImageProcessor<> imageProcessor(srcData, srcDataBytes);
            if (imageProcessor.IsValid())
            {
                m_imageData = std::move(imageProcessor.GetImageData());
                m_width = imageProcessor.GetWidth();
                m_height = imageProcessor.GetHeight();
                m_channels = imageProcessor.GetChannels();
                m_colorDepth = imageProcessor.GetColorDepth();
                m_pixelFormat = imageProcessor.GetPixelFormat();
                return true;
            }
        }
        return false;

    case ImageFormat::Jpg:
        {
            JpgImageProcessor<> imageProcessor(srcData, srcDataBytes);
            if (imageProcessor.IsValid())
            {
                m_imageData = std::move(imageProcessor.GetImageData());
                m_width = imageProcessor.GetWidth();
                m_height = imageProcessor.GetHeight();
                m_channels = imageProcessor.GetChannels();
                m_colorDepth = imageProcessor.GetColorDepth();
                m_pixelFormat = imageProcessor.GetPixelFormat();
                return true;
            }
        }
        return false;

    case ImageFormat::WebP:
        {
            WebPImageProcessor<> imageProcessor(srcData, srcDataBytes);
            if (imageProcessor.IsValid())
            {
                m_imageData = std::move(imageProcessor.GetImageData());
                m_width = imageProcessor.GetWidth();
                m_height = imageProcessor.GetHeight();
                m_channels = imageProcessor.GetChannels();
                m_colorDepth = imageProcessor.GetColorDepth();
                m_pixelFormat = imageProcessor.GetPixelFormat();
                return true;
            }
        }
        return false;

    case ImageFormat::Bmp:
        {
            BmpImageProcessor<> imageProcessor(srcData, srcDataBytes);
            if (imageProcessor.IsValid())
            {
                m_imageData = std::move(imageProcessor.GetImageData());
                m_width = imageProcessor.GetWidth();
                m_height = imageProcessor.GetHeight();
                m_channels = imageProcessor.GetChannels();
                m_colorDepth = imageProcessor.GetColorDepth();
                m_pixelFormat = imageProcessor.GetPixelFormat();
                return true;
            }
        }
        return false;

    default:
        return false;
    }
}

bool Image::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
{
    ImageFormat imageFormat = ImageFormat::Unknown;
    if (PngImageProcessor<>::VerifyFormat(srcData, srcDataBytes))
    {
        imageFormat = ImageFormat::Png;
    }
    else if (JpgImageProcessor<>::VerifyFormat(srcData, srcDataBytes))
    {
        imageFormat = ImageFormat::Jpg;
    }
    else if (WebPImageProcessor<>::VerifyFormat(srcData, srcDataBytes))
    {
        imageFormat = ImageFormat::WebP;
    }
    else if (BmpImageProcessor<>::VerifyFormat(srcData, srcDataBytes))
    {
        imageFormat = ImageFormat::Bmp;
    }
    else
    {
        return false;
    }

    return this->Initialize(filePath, srcData, srcDataBytes, imageFormat);
}

bool Image::IsValid() const noexcept
{
    return m_imageData.size() > 0;
}

std::vector<uint8_t>& Image::GetImageData() noexcept
{
    return m_imageData;
}

const std::vector<uint8_t>& Image::GetImageData() const noexcept
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

int32_t Image::GetChannels() const noexcept
{
    return m_channels;
}

int32_t Image::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

PixelFormat Image::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

const std::string& Image::GetFilePath() const noexcept
{
    return m_filePath;
}

} /* namespace tgon */