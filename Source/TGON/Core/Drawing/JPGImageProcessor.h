/**
 * @filename    JPGImageProcessor.h
 * @author      ggomdyu
 * @since       04/22/2018
 */

#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <string>
#include <png.h>

#include "ImageType.h"

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class JPGImageProcessor
{
/* @section Public constructor */
public:
    JPGImageProcessor() noexcept;
    JPGImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes);

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly PNG. */
    static bool VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes);
    bool Import(const uint8_t* srcData, uint32_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetImageData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetImageData() const noexcept;
    int32_t GetWidth() const noexcept;
    int32_t GetHeight() const noexcept;
    int32_t GetColorDepth() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;

/* @section Private variable */
private:
    std::vector<uint8_t, _AllocatorType> m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_colorDepth;
    int32_t m_channels;
    PixelFormat m_pixelFormat;
};

template <typename _AllocatorType>
inline JPGImageProcessor<_AllocatorType>::JPGImageProcessor() noexcept :
    m_width(0),
    m_height(0),
    m_colorDepth(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

template <typename _AllocatorType>
inline JPGImageProcessor<_AllocatorType>::JPGImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes) :
    JPGImageProcessor()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _AllocatorType>
inline bool JPGImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    return false;
}

template<typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& JPGImageProcessor<_AllocatorType>::GetImageData() noexcept
{
    return m_imageData;
}

template<typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& JPGImageProcessor<_AllocatorType>::GetImageData() const noexcept
{
    return m_imageData;
}

template <typename _AllocatorType>
inline bool JPGImageProcessor<_AllocatorType>::IsValid() const noexcept
{
    return m_imageData.size() > 0;
}

template <typename _AllocatorType>
inline int32_t JPGImageProcessor<_AllocatorType>::GetWidth() const noexcept
{
    return m_width;
}

template <typename _AllocatorType>
inline int32_t JPGImageProcessor<_AllocatorType>::GetHeight() const noexcept
{
    return m_height;
}

template <typename _AllocatorType>
inline int32_t JPGImageProcessor<_AllocatorType>::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

template <typename _AllocatorType>
inline int32_t JPGImageProcessor<_AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _AllocatorType>
inline PixelFormat JPGImageProcessor<_AllocatorType>::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

template <typename _AllocatorType>
inline bool JPGImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    return (srcData[0] == 0xFF && srcData[1] == 0xD8);
}

} /* namespace tgon */