#include "PrecompiledHeader.pch"

#include <cstdint>
#include <png.h>

#include "Core/Debug/Log.h"
#include "Core/Hash/Hash.h"
#include "Core/String/StringTraits.h"

#include "Image.h"
#include "ImageUtility.h"
#include "PNGImageProcessor.h"
//#include "JPGImageProcessor.h"
//#include "BMPImageProcessor.h"
//#include "WebPImageProcessor.h"

namespace tgon
{
namespace
{

// Currently support windows format, not os2
template <typename _AllocatorType>
bool ResolveBMP(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t, _AllocatorType>* destData, int32_t* width, int32_t* height, int32_t* channels, int32_t* colorDepth, PixelFormat* pixelFormat)
{
    if (srcData[0] != 'B' || srcData[1] != 'M')
    {
        return false;
    }

    *width = *(int*)&(srcData[0x12]);
    *height = *(int*)&(srcData[0x16]);

    int imageSize = *(int*)&(srcData[0x22]);
    destData->resize(imageSize);

    int dataStartPos = *(int*)&(srcData[0x0A]);
    if (dataStartPos == 0)
    {
        dataStartPos = 54;
    }

    memcpy(destData->data(), srcData + dataStartPos, imageSize);

    return true;
}

} /* namespace */

Image::Image(const std::string& filePath) :
    Image([&]() -> Image
    {
        FILE* file = fopen(filePath.c_str(), "rb");
        if (file == nullptr)
        {
            return {};
        }

        // Read the image data from file.
        std::vector<uint8_t> imageData;
        {
            fseek(file, 0, SEEK_END);
            long fileSize = ftell(file);
            fseek(file, 0, SEEK_SET);

            imageData.resize(fileSize + 1);
            fread(imageData.data(), 1, fileSize, file);
        };
        fclose(file);

        std::size_t extensionOffset = filePath.rfind('.') + 1;
        return Image(ConvertStringToImageFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset), imageData.data(), imageData.size());
    } ())
{
}

Image::Image(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes) :
    Image()
{
    switch (imageFormat)
    {
    case ImageFormat::BMP:
        ResolveBMP(srcData, srcDataBytes, &m_imageData, &m_width, &m_height, &m_channels, &m_colorDepth, &m_pixelFormat);
        break;

    //case ImageFormat::JPG:
        //ResolveJPG(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, nullptr, &m_depth, &m_pixelFormat);
        //break;

    //case ImageFormat::WEBP:
        //ResolveWEBP(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, nullptr, &m_depth, &m_pixelFormat);
        //break;

    case ImageFormat::PNG:
        {
            PNGImageProcessor<> imageProcessor(srcData, srcDataBytes);
            if (imageProcessor.IsValid())
            {
                m_imageData = imageProcessor.GetImageData();
                m_width = imageProcessor.GetWidth();
                m_height = imageProcessor.GetHeight();
                m_channels = imageProcessor.GetChannels();
                m_colorDepth = imageProcessor.GetColorDepth();
                m_pixelFormat = imageProcessor.GetPixelFormat();
            }
        }
        break;

    default:
        Log("%s image format isn't currently supported.", ConvertImageFormatToString(imageFormat));
        break;
    }
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

Image::Image() :
    m_width(0),
    m_height(0),
    m_channels(0),
    m_colorDepth(0),
    m_pixelFormat(PixelFormat::Unknown)
{
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