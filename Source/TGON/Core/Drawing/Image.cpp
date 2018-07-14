#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core/Debug/Log.h"

#include "Image.h"
#include "ImageUtility.h"

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
    m_filePath = filePath;
    
    stbi_uc* imageData = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channels, 4);
    if (imageData == nullptr)
    {
        return false;
    }
    
    m_pixelFormat = PixelFormat::R8G8B8A8_Unorm;
    m_imageData.reset(reinterpret_cast<uint8_t*>(imageData));
    
    return true;
}

bool Image::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
{
    m_filePath = filePath;

    stbi_uc* imageData = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(srcData), srcDataBytes, &m_width, &m_height, &m_channels, 4);
    if (imageData == nullptr)
    {
        return false;
    }
    
    m_pixelFormat = PixelFormat::R8G8B8A8_Unorm;
    m_imageData.reset(reinterpret_cast<uint8_t*>(imageData));
    
    return true;
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
