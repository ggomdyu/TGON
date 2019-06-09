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

template <typename _DerivedType>
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
    std::unique_ptr<uint8_t[]>& GetImageData() noexcept;
    const std::unique_ptr<uint8_t[]>& GetImageData() const noexcept;
    int32_t GetWidth() const noexcept;
    int32_t GetHeight() const noexcept;
    int32_t GetColorDepth() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;

/* @section Variable */
protected:
    std::unique_ptr<uint8_t[]> m_imageData;
    int32_t m_width;
    int32_t m_height;
    int32_t m_colorDepth;
    int32_t m_channels;
    PixelFormat m_pixelFormat;
};

template <typename _DerivedType>
inline BaseImageProcessor<_DerivedType>::BaseImageProcessor() noexcept :
    m_width(0),
    m_height(0),
    m_colorDepth(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

template <typename _DerivedType>
inline BaseImageProcessor<_DerivedType>::BaseImageProcessor(const uint8_t* srcData, size_t srcDataBytes) :
    BaseImageProcessor()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _DerivedType>
inline bool BaseImageProcessor<_DerivedType>::Import(const uint8_t* srcData, size_t srcDataBytes)
{
    return static_cast<_DerivedType*>(this)->Import(srcData, srcDataBytes);
}

template <typename _DerivedType>
inline std::unique_ptr<uint8_t[]>& BaseImageProcessor<_DerivedType>::GetImageData() noexcept
{
    return m_imageData;
}

template <typename _DerivedType>
inline const std::unique_ptr<uint8_t[]>& BaseImageProcessor<_DerivedType>::GetImageData() const noexcept
{
    return m_imageData;
}

template <typename _DerivedType>
inline bool BaseImageProcessor<_DerivedType>::IsValid() const noexcept
{
    return m_imageData != nullptr;
}

template <typename _DerivedType>
inline int32_t BaseImageProcessor<_DerivedType>::GetWidth() const noexcept
{
    return m_width;
}

template <typename _DerivedType>
inline int32_t BaseImageProcessor<_DerivedType>::GetHeight() const noexcept
{
    return m_height;
}

template <typename _DerivedType>
inline int32_t BaseImageProcessor<_DerivedType>::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

template <typename _DerivedType>
inline int32_t BaseImageProcessor<_DerivedType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _DerivedType>
inline PixelFormat BaseImageProcessor<_DerivedType>::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

template <typename _DerivedType>
inline bool BaseImageProcessor<_DerivedType>::VerifyFormat(const uint8_t* srcData, size_t srcDataBytes)
{
    return _DerivedType::VerifyFormat(srcData, srcDataBytes);
}

} /* namespace tgon */  
