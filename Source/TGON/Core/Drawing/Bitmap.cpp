#include "PrecompiledHeader.pch"

#include "Bitmap.h"

//#include <boost/filesystem/fstream.hpp>
#include <cstdint>
#include <png.h>
#include <windows.h>

namespace tgon
{
namespace core
{
namespace
{

bool DecodePNG(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel, PixelFormat* pixelFormat)
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
            uint8_t* data;
            int size;
            int offset;
        } imageSource{(unsigned char*)srcData, srcDataLen, 0};
        
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
    *bitsPerPixel = png_get_bit_depth(pngStruct, pngInfo) * 4;



    png_uint_32 colorType = png_get_color_type(pngStruct, pngInfo);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngStruct);
    }
    else if (colorType == PNG_COLOR_TYPE_GRAY && *bitsPerPixel < 8)
    {
        png_set_expand_gray_1_2_4_to_8(pngStruct);
    }

    // Expand tRNS chunk data to full alpha channel.
    if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(pngStruct);
    }

    if (*bitsPerPixel == 16)
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

        // TODO: More Effective way is using Memory Pool!
        std::unique_ptr<png_byte*> rowPointer(reinterpret_cast<png_byte**>(operator new(sizeof(png_byte*) * (*height))));
        for (std::size_t i = 0; i < *height; ++i)
        {
            rowPointer.get()[i] = destData->data() + i * rowBytes;
        }

        png_read_image(pngStruct, rowPointer.get());

        png_read_end(pngStruct, nullptr);
    }
        
    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);

    return true;
}

bool DecodePNG(const std::vector<uint8_t>& srcData, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel, PixelFormat* pixelFormat)
{
    return DecodePNG(srcData.data(), srcData.size(), destData, width, height, bitsPerPixel, pixelFormat);
}

bool DecodeJPG(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel, PixelFormat* pixelFormat)
{
    return true;
}

// Currently support windows format, not os2
bool DecodeBMP(const uint8_t* srcData, std::size_t srcDataLen, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel, PixelFormat* pixelFormat)
{
    return true;
}

} /* namespace */

Bitmap::Bitmap(const std::string& filePath) :
    m_filePath(filePath)
{
    // TODO: Implement Engine file loader
    FILE* file = nullptr;
    fopen_s(&file, filePath.c_str(), "rb");
    if (file == nullptr)
    {
        return;
    }

    std::vector<uint8_t> imageData;
    // Resize the vector by file size.
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    imageData.resize(fileSize + 1);
    fseek(file, 0, SEEK_SET);

    fread(imageData.data(), 1, fileSize, file);

    std::size_t extensionOffset = filePath.rfind('.') + 1;
    new (this) Bitmap(ConvertStringToImageFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset), imageData.data(), imageData.size());
}

Bitmap::Bitmap(ImageFormat imageFormat, const uint8_t* srcData, std::size_t srcDataBytes) :
    m_bitsPerPixel(0),
    m_width(0),
    m_height(0)
{
    switch (imageFormat)
    {
    case ImageFormat::BMP:
        DecodeBMP(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_bitsPerPixel, &m_pixelFormat);
        break;

    case ImageFormat::JPG:
        DecodeJPG(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_bitsPerPixel, &m_pixelFormat);
        break;

    case ImageFormat::PNG:
        DecodePNG(srcData, srcDataBytes, &m_bits, &m_width, &m_height, &m_bitsPerPixel, &m_pixelFormat);
        break;
    }
}

uint8_t& Bitmap::operator[](std::size_t index)
{
    return m_bits[index];
}

const uint8_t& Bitmap::operator[](std::size_t index) const
{
    return m_bits[index];
}

std::vector<uint8_t>& Bitmap::GetBits()
{
    return m_bits;
}

const std::vector<uint8_t>& Bitmap::GetBits() const
{
    return m_bits;
}

int32_t Bitmap::GetBitsPerPixel() const
{
    return m_bitsPerPixel;
}

PixelFormat Bitmap::GetPixelFormat() const
{
    return m_pixelFormat;
}

int32_t Bitmap::GetWidth() const
{
    return m_width;
}

int32_t Bitmap::GetHeight() const
{
    return m_height;
}

const std::string& Bitmap::GetFilePath() const
{
    return m_filePath;
}

} /* namespace core */
} /* namespace tgon */