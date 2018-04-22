/**
 * @filename    BMPImageProcessor.h
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
class BMPImageProcessor
{
/* @section Public constructor */
public:
    BMPImageProcessor() noexcept;
    BMPImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes);

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
inline BMPImageProcessor<_AllocatorType>::BMPImageProcessor() noexcept :
    m_width(0),
    m_height(0),
    m_colorDepth(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

template <typename _AllocatorType>
inline BMPImageProcessor<_AllocatorType>::BMPImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes) :
    BMPImageProcessor()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _AllocatorType>
inline bool BMPImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    return false;
}

template<typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& BMPImageProcessor<_AllocatorType>::GetImageData() noexcept
{
    return m_imageData;
}

template<typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& BMPImageProcessor<_AllocatorType>::GetImageData() const noexcept
{
    return m_imageData;
}

template <typename _AllocatorType>
inline bool BMPImageProcessor<_AllocatorType>::IsValid() const noexcept
{
    return m_imageData.size() > 0;
}

template <typename _AllocatorType>
inline int32_t BMPImageProcessor<_AllocatorType>::GetWidth() const noexcept
{
    return m_width;
}

template <typename _AllocatorType>
inline int32_t BMPImageProcessor<_AllocatorType>::GetHeight() const noexcept
{
    return m_height;
}

template <typename _AllocatorType>
inline int32_t BMPImageProcessor<_AllocatorType>::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

template <typename _AllocatorType>
inline int32_t BMPImageProcessor<_AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _AllocatorType>
inline PixelFormat BMPImageProcessor<_AllocatorType>::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

template <typename _AllocatorType>
inline bool BMPImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&srcData[0]);
    return (header[0] = 'B' && header[1] = 'M');
}

} /* namespace tgon */  

//namespace
//{
//
//// Currently support windows format, not os2
//template <typename _AllocatorType>
//bool ResolveBMP(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t, _AllocatorType>* destData, int32_t* width, int32_t* height, int32_t* channels, int32_t* colorDepth, PixelFormat* pixelFormat)
//{
//    if (srcData[0] != 'B' || srcData[1] != 'M')
//    {
//        return false;
//    }
//
//    *width = *(int*)&(srcData[0x12]);
//    *height = *(int*)&(srcData[0x16]);
//
//    int imageSize = *(int*)&(srcData[0x22]);
//    destData->resize(imageSize);
//
//    int dataStartPos = *(int*)&(srcData[0x0A]);
//    if (dataStartPos == 0)
//    {
//        dataStartPos = 54;
//    }
//
//    memcpy(destData->data(), srcData + dataStartPos, imageSize);
//
//    return true;
//}
//
//} /* namespace */