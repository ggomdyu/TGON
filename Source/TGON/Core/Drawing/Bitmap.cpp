#include "PrecompiledHeader.pch"

#include "Bitmap.h"

#include "Core/Debug/Log.h"

#include <cstdint>
#include <png.h>

namespace tgon
{
namespace core
{
namespace
{

template <typename _AllocatorType>
bool ResolvePNG(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t, _AllocatorType>* destData, int32_t* width, int32_t* height, int32_t* channels, int32_t* colorDepth, PixelFormat* pixelFormat)
{
    // Read the first 8 bytes of the file and make sure they match the PNG signature bytes.
    bool isPNGFormat = png_sig_cmp(srcData, 0, 8) == 0;
    if (isPNGFormat == false)
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
            int size;
            const uint8_t* data;
            int offset;
        } imageSource{static_cast<int>(srcDataLen), (const uint8_t*)srcData, 0};
        
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

    *width = png_get_image_width(pngStruct, pngInfo);
    *height = png_get_image_height(pngStruct, pngInfo);
    *colorDepth = png_get_bit_depth(pngStruct, pngInfo);
    *channels = png_get_channels(pngStruct, pngInfo);
    *pixelFormat = PixelFormat::R8G8B8A8_UNORM;
    
    png_uint_32 colorType = png_get_color_type(pngStruct, pngInfo);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngStruct);
    }
    
    else if (colorType == PNG_COLOR_TYPE_GRAY && *colorDepth < 8)
    {
        png_set_expand_gray_1_2_4_to_8(pngStruct);
    }

    // Expand tRNS chunk data to full alpha channel.
    if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(pngStruct);
    }

    if (*colorDepth == 16)
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
        std::size_t destDataLen = sizeof(png_byte*) * (*height) * rowBytes;
        destData->resize(destDataLen);

        thread_local static std::vector<png_byte*> rowPointer;
        rowPointer.resize(*height);

        for (std::size_t i = 0; i < *height; ++i)
        {
            rowPointer[i] = destData->data() + i * rowBytes;
        }

        png_read_image(pngStruct, rowPointer.data());

        png_read_end(pngStruct, nullptr);
    }
        
    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);

    return true;
}

template <typename _AllocatorType>
bool ResolveJPG(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t, _AllocatorType>* destData, int32_t* width, int32_t* height, int32_t* channels, int32_t* colorDepth, PixelFormat* pixelFormat)
{
    return true;
}

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

Bitmap::Bitmap(const std::string& filePath) :
    m_width(0),
    m_height(0),
    m_channels(0),
    m_colorDepth(0),
    m_pixelFormat(PixelFormat::Unknown),
    m_filePath(filePath)
{
    // TODO: Implement Engine file loader
    FILE* file = fopen(filePath.c_str(), "rb");
    {
        if (file == nullptr)
        {
            return;
        }

        // Resize the vector by file size.
        std::vector<uint8_t> imageData;
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        imageData.resize(fileSize + 1);
        fseek(file, 0, SEEK_SET);

        fread(imageData.data(), 1, fileSize, file);

        std::size_t extensionOffset = filePath.rfind('.') + 1;
        *this = Bitmap(ConvertStringToImageFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset), imageData.data(), imageData.size());
    }
    fclose(file);
}

Bitmap::Bitmap(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes) :
    m_width(0),
    m_height(0),
    m_channels(0),
    m_colorDepth(0),
    m_pixelFormat(PixelFormat::Unknown)
{
    switch (imageFormat)
    {
    case ImageFormat::BMP:
        ResolveBMP(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, &m_colorDepth, &m_pixelFormat);
        break;

    //case ImageFormat::JPG:
        //ResolveJPG(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, nullptr, &m_depth, &m_pixelFormat);
        //break;

    //case ImageFormat::WEBP:
        //ResolveWEBP(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, nullptr, &m_depth, &m_pixelFormat);
        //break;

    case ImageFormat::PNG:
        ResolvePNG(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_channels, &m_colorDepth, &m_pixelFormat);
        break;

    default:
        core::Log("%s image format isn't currently supported.", ConvertImageFormatToString(imageFormat));
        break;
    }
}

Bitmap::Bitmap(Bitmap&& rhs) :
    m_bits(std::move(rhs.m_bits)),
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

Bitmap& Bitmap::operator=(Bitmap&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    m_bits = std::move(rhs.m_bits);
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

uint8_t& Bitmap::operator[](std::size_t index)
{
    return m_bits[index];
}

const uint8_t& Bitmap::operator[](std::size_t index) const
{
    return m_bits[index];
}

bool Bitmap::IsValid() const noexcept
{
    return m_bits.size() > 0;
}

std::vector<uint8_t>& Bitmap::GetBits() noexcept
{
    return m_bits;
}

const std::vector<uint8_t>& Bitmap::GetBits() const noexcept
{
    return m_bits;
}

int32_t Bitmap::GetBitsPerPixel() const noexcept
{
    return m_colorDepth / sizeof(int8_t) * m_channels;
}

int32_t Bitmap::GetWidth() const noexcept
{
    return m_width;
}

int32_t Bitmap::GetHeight() const noexcept
{
    return m_height;
}

int32_t Bitmap::GetChannels() const noexcept
{
    return m_channels;
}

int32_t Bitmap::GetColorDepth() const noexcept
{
    return m_colorDepth;
}

PixelFormat Bitmap::GetPixelFormat() const noexcept
{
    return m_pixelFormat;
}

const std::string& Bitmap::GetFilePath() const noexcept
{
    return m_filePath;
}

} /* namespace core */
} /* namespace tgon */
