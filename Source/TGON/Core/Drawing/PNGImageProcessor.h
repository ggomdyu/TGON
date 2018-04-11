/**
 * @filename    PNGImageProcessor.h
 * @author      ggomdyu
 * @since       01/20/2018
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
class PNGImageProcessor
{
/* @section Public constructor */
public:
    PNGImageProcessor() noexcept;
    PNGImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes);

/* @section Public method */
public:
    bool Import(const uint8_t* srcData, uint32_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetImageData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetImageData() const noexcept;
    int32_t GetWidth() const noexcept;
    int32_t GetHeight() const noexcept;
    int32_t GetColorDepth() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;

/* @section Private method */
private:
    /* @brief   Verifies the importing file is exactly PNG. */
    bool VerifyFormat(const uint8_t* srcData) const;

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
inline PNGImageProcessor<_AllocatorType>::PNGImageProcessor() noexcept :
    m_width(0),
    m_height(0),
    m_colorDepth(0),
    m_channels(0),
    m_pixelFormat(PixelFormat::Unknown)
{
}

template <typename _AllocatorType>
inline PNGImageProcessor<_AllocatorType>::PNGImageProcessor(const uint8_t* srcData, uint32_t srcDataBytes) :
    PNGImageProcessor()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _AllocatorType>
inline bool PNGImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (this->VerifyFormat(srcData) == false)
    {
        return false;
    }

    // Allocate and initialize a png_struct structure.
    // You can pass pointers to error handling functions, and a pointer to a data struct 
    // for use by the error functions, if necessary (the pointer and functions can be NULL if the default error handlers are to be used).
    png_structp pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (pngStruct == nullptr)
    {
        return false;
    }

    png_infop pngInfo = png_create_info_struct(pngStruct);
    if (pngInfo == nullptr)
    {
        png_destroy_read_struct(&pngStruct, nullptr, nullptr);
        return false;
    }

    // We can change the method of I/O. libPNG supplies callbacks that you can set through the function png_set_read_fn() at run time.
    // We will use it for reading PNG Images from memory.
    {
        struct ImageSource
        {
            int size; // TODO: uint32_t로 바꾸기
            const uint8_t* data;
            int offset;
        } imageSource{static_cast<int>(srcDataBytes), (const uint8_t*)srcData, 0};

        png_set_read_fn(pngStruct, &imageSource, [](png_structp pngStruct, png_bytep data, png_size_t dataLen)
        {
            ImageSource* imageSource = reinterpret_cast<ImageSource*>(png_get_io_ptr(pngStruct));

            if (static_cast<decltype(imageSource->size)>(imageSource->offset + dataLen) <= imageSource->size)
            {
                memcpy(data, imageSource->data + imageSource->offset, dataLen);
                imageSource->offset += dataLen;
            }
        });
    }

    // Set error handling with setjmp.
    // Unless if you set up your own error handlers in the png_create_read_struct earlier.
    if (setjmp(png_jmpbuf(pngStruct)))
    {
        png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
        return false;
    }

    // Read the PNG file information.
    png_read_info(pngStruct, pngInfo);

    m_width = png_get_image_width(pngStruct, pngInfo);
    m_height = png_get_image_height(pngStruct, pngInfo);
    m_colorDepth = png_get_bit_depth(pngStruct, pngInfo);
    m_channels = png_get_channels(pngStruct, pngInfo);
    m_pixelFormat = PixelFormat::R8G8B8A8_UNORM;

    png_uint_32 colorType = png_get_color_type(pngStruct, pngInfo);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngStruct);
    }

    else if (colorType == PNG_COLOR_TYPE_GRAY && m_colorDepth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(pngStruct);
    }

    // Expand tRNS chunk data to full alpha channel.
    if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(pngStruct);
    }

    if (m_colorDepth == 16)
    {
        png_set_strip_16(pngStruct);
    }

    // If color type has no alpha channel, then fill it with 0xff.
    if (colorType = PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_filler(pngStruct, 0xff, PNG_FILLER_AFTER);
    }
    // If the image is grayscale, then expand it to 24-bit RGB.
    if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(pngStruct);
    }

    png_read_update_info(pngStruct, pngInfo);

    // Start reading the image.
    {
        png_size_t rowBytes = png_get_rowbytes(pngStruct, pngInfo);
        std::size_t imageDataBytes = sizeof(png_byte*) * (m_height) * rowBytes;
        m_imageData.resize(imageDataBytes);

        thread_local static std::vector<png_byte*> rowPointer;
        rowPointer.resize(m_height);

        for (std::size_t i = 0; i < m_height; ++i)
        {
            rowPointer[i] = m_imageData.data() + i * rowBytes;
        }

        png_read_image(pngStruct, rowPointer.data());
        png_read_end(pngStruct, nullptr);
    }

    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
    return true;
}

template<typename _AllocatorType>
inline std::vector<uint8_t, _AllocatorType>& PNGImageProcessor<_AllocatorType>::GetImageData() noexcept
{
    return m_imageData;
}

template<typename _AllocatorType>
inline const std::vector<uint8_t, _AllocatorType>& PNGImageProcessor<_AllocatorType>::GetImageData() const noexcept
{
    return m_imageData;
}

template <typename _AllocatorType>
inline bool PNGImageProcessor<_AllocatorType>::IsValid() const noexcept
{
    return m_imageData.size() > 0;
}

template <typename _AllocatorType>
inline int32_t PNGImageProcessor<_AllocatorType>::GetWidth() const noexcept
{
    return m_width;
}

template <typename _AllocatorType>
inline int32_t PNGImageProcessor<_AllocatorType>::GetHeight() const noexcept
{
    return m_height;
}

template <typename _AllocatorType>
inline int32_t PNGImageProcessor<_AllocatorType>::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

template <typename _AllocatorType>
inline int32_t PNGImageProcessor<_AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _AllocatorType>
inline PixelFormat PNGImageProcessor<_AllocatorType>::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

template <typename _AllocatorType>
inline bool PNGImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData) const
{
    // Read the first 8 bytes of the file and make sure they match the PNG signature bytes.
    bool isPNGFormat = png_sig_cmp(srcData, 0, 8) == 0;
    return isPNGFormat;
}

} /* namespace tgon */  