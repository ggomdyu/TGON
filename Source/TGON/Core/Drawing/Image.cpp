#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Core/Debug/Log.h"

#include "Image.h"
#include "ImageUtility.h"

namespace tgon
{

Image::Image() :
    m_imageData(nullptr),
    m_width(0),
    m_height(0),
    m_channels(0)
{
}

Image::Image(const std::string& filePath) :
    Image()
{
    this->Initialize(filePath);
}

Image::Image(const std::string& filePath, const uint8_t* srcData, int32_t srcDataBytes) :
    Image()
{
    this->Initialize(filePath, srcData, srcDataBytes);
}

Image::Image(Image&& rhs) :
    m_imageData(rhs.m_imageData),
    m_width(rhs.m_width),
    m_height(rhs.m_height),
    m_channels(rhs.m_channels),
    m_filePath(std::move(rhs.m_filePath))
{
    rhs.m_imageData = nullptr;
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;
}
    
Image::~Image()
{
    if (m_imageData != nullptr)
    {
        stbi_image_free(m_imageData);
        m_imageData = nullptr;
    }
}

Image& Image::operator=(Image&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    m_imageData = rhs.m_imageData;
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_channels = rhs.m_channels;
    m_filePath = std::move(rhs.m_filePath);

    rhs.m_imageData = nullptr;
    rhs.m_width = 0;
    rhs.m_height = 0;
    rhs.m_channels = 0;

    return *this;
}

uint8_t& Image::operator[](std::size_t index)
{
    return m_imageData[index];
}

const uint8_t Image::operator[](std::size_t index) const
{
    return m_imageData[index];
}

bool Image::Initialize(const std::string& filePath)
{
    m_filePath = filePath;
    
    m_imageData = stbi_load(filePath.c_str(), &m_width, &m_height, &m_channels, 4);
    if (m_imageData == nullptr)
    {
        return false;
    }
    
    return true;
}

bool Image::Initialize(const std::string& filePath, const uint8_t* srcData, int32_t srcDataBytes)
{
    m_filePath = filePath;

    m_imageData = stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(srcData), srcDataBytes, &m_width, &m_height, &m_channels, 4);
    if (m_imageData == nullptr)
    {
        return false;
    }
    
    return true;
}

bool Image::IsValid() const noexcept
{
    return m_imageData != nullptr;
}

uint8_t* Image::GetImageData() noexcept
{
    return m_imageData;
}

const uint8_t* Image::GetImageData() const noexcept
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

PixelFormat Image::GetPixelFormat() const noexcept
{
    return PixelFormat::R8G8B8A8_Unorm;
}

const std::string& Image::GetFilePath() const noexcept
{
    return m_filePath;
}

} /* namespace tgon */
