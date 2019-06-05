/**
 * @file    BaseImageProcessor.h
 * @author  ggomdyu
 * @since   01/20/2018
 */

#pragma once
#include <vector>
#include <cstdint>
#include <memory>

#include "../ImageType.h"

namespace tgon
{

template <typename _DerivedType, typename _AllocatorType = std::allocator<uint8_t>>
class BaseImageProcessor
{
/* @section Constructor */
public:
    BaseImageProcessor() noexcept;
    BaseImageProcessor(const uint8_t* srcData, size_t srcDataBytes);

/* @section Method */
public:
    static bool VerifyFormat(const uint8_t* srcData, size_t srcDataBytes);
    bool Import(const uint8_t* srcData, size_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetImageData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetImageData() const noexcept;
    int32_t GetWidth() const noexcept;
    int32_t GetHeight() const noexcept;
    int32_t GetColorDepth() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;

/* @section Variable */
protected:
    std::vector<uint8_t, _AllocatorType> m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_colorDepth;
    int32_t m_channels;
    PixelFormat m_pixelFormat;
};

template <typename _DerivedType, typename _AllocatorType>
inline BaseImageProcessor<_DerivedType, _AllocatorType>::BaseImageProcessor() noexcept :
    m_width(0),
    m_height(0),
    m_colorDepth(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

template <typename _DerivedType, typename _AllocatorType>
inline BaseImageProcessor<_DerivedType, _AllocatorType>::BaseImageProcessor(const uint8_t* srcData, size_t srcDataBytes) :
    BaseImageProcessor()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _DerivedType, typename _AllocatorType>
inline bool BaseImageProcessor<_DerivedType, _AllocatorType>::Import(const uint8_t* srcData, size_t srcDataBytes)
{
    return static_cast<_DerivedType*>(this)->Import(srcData, srcDataBytes);
}

template <typename _DerivedType, typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& BaseImageProcessor<_DerivedType, _AllocatorType>::GetImageData() noexcept
{
    return m_imageData;
}

template <typename _DerivedType, typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& BaseImageProcessor<_DerivedType, _AllocatorType>::GetImageData() const noexcept
{
    return m_imageData;
}

template <typename _DerivedType, typename _AllocatorType>
inline bool BaseImageProcessor<_DerivedType, _AllocatorType>::IsValid() const noexcept
{
    return m_imageData.size() > 0;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t BaseImageProcessor<_DerivedType, _AllocatorType>::GetWidth() const noexcept
{
    return m_width;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t BaseImageProcessor<_DerivedType, _AllocatorType>::GetHeight() const noexcept
{
    return m_height;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t BaseImageProcessor<_DerivedType, _AllocatorType>::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

template <typename _DerivedType, typename _AllocatorType>
inline int32_t BaseImageProcessor<_DerivedType, _AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _DerivedType, typename _AllocatorType>
inline PixelFormat BaseImageProcessor<_DerivedType, _AllocatorType>::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

template <typename _DerivedType, typename _AllocatorType>
inline bool BaseImageProcessor<_DerivedType, _AllocatorType>::VerifyFormat(const uint8_t* srcData, size_t srcDataBytes)
{
    return _DerivedType::VerifyFormat(srcData, srcDataBytes);
}

} /* namespace tgon */  
