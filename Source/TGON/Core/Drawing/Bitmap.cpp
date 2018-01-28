#include "PrecompiledHeader.pch"

#include "Bitmap.h"

//#include <boost/filesystem/fstream.hpp>
#include <cstdint>
#include <algorithm>
#include <png.h>
#include <windows.h>

namespace tgon
{
namespace core
{
namespace
{

bool DecodePNG(const uint8_t* srcData, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel)
{
    FILE* file = nullptr;
    fopen_s(&file, "E:/Users/ggomdyu/Desktop/image.png", "rb");
    if (file == nullptr)
    {
        return false;
    }

    // Read the first 8 bytes of the file and make sure they match the PNG signature bytes.
    bool isPNGFormat = png_sig_cmp(srcData, 0, 8) == 0;
    if (isPNGFormat == false)
    {
        // If image is not PNG, there is no need to waste time setting up libpng.
        return false;
    }

    // We will pass pointers to error handling functions, and a pointer to a data struct for use by the error functions, if necessary (the pointer and functions can be NULL if the default error handlers are to be used).
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

    png_init_io(pngStruct, file);

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
    *bitsPerPixel = png_get_bit_depth(pngStruct, pngInfo);

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

    png_size_t rowBytes = png_get_rowbytes(pngStruct, pngInfo);
    std::size_t destDataLen = sizeof(png_byte*) * (*height) * rowBytes;
    destData->resize(destDataLen);

    std::unique_ptr<png_byte*> rowPointer(reinterpret_cast<png_byte**>(operator new(sizeof(png_byte*) * (*height))));
    for (std::size_t i = 0; i < *height; ++i)
    {
        rowPointer.get()[i] = destData->data() + i * rowBytes;
    }

    png_read_image(pngStruct, rowPointer.get());

    png_read_end(pngStruct, nullptr);
        
    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);

    return true;
}
    
bool DecodeJPG(const char* filePath, std::vector<uint8_t>* bits, int32_t* width, int32_t* height, int32_t* bitsPerPixel)
{
    return true;
}

// Currently support windows format, not os2
bool DecodeBMP(const uint8_t* srcData, std::vector<uint8_t>* destData, int32_t* width, int32_t* height, int32_t* bitsPerPixel)
{   
    constexpr std::size_t headerSize = 54;

    // Verify that srcData has bmp data.
    int16_t signiture = *reinterpret_cast<const int16_t*>(&srcData[0]);
    if (signiture != 0x4D42)
    {
        return false;
    }

    *width = *reinterpret_cast<const int32_t*>(&srcData[18]);
    *height = *reinterpret_cast<const int32_t*>(&srcData[22]);
    *bitsPerPixel = *reinterpret_cast<const int32_t*>(&srcData[28]);

    if (*bitsPerPixel == 24)
    {
        std::size_t destDataLen = (*width) * (*height) * 3;
        destData->resize(destDataLen);

        const uint8_t* srcDataIter = srcData + headerSize;
        int accumulatedIndex = 0;
        for (int y = 0; y < *height; ++y)
        {
            for (int x = 0; x < *width; ++x)
            {
                (*destData)[accumulatedIndex++] = srcDataIter[2];
                (*destData)[accumulatedIndex++] = srcDataIter[1];
                (*destData)[accumulatedIndex++] = srcDataIter[0];

                srcDataIter += 3;
            }
        }
    }
    else if (*bitsPerPixel == 16)
    {

    }
    else if (*bitsPerPixel == 8)
    {

    }
    else if (*bitsPerPixel == 1)
    {

    }

    return false;
}

}

Bitmap::Bitmap(const std::string& filePath) :
    m_filePath(filePath),
    m_bitsPerPixel(0),
    m_width(0),
    m_height(0)
{
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


    const auto extension = filePath.cbegin() + filePath.rfind('.') + 1;

    char lowercaseExtension[5] {};
    std::transform(extension, filePath.end(), lowercaseExtension, ::tolower);

    if (std::strcmp(lowercaseExtension, "png") == 0)
    {
        DecodePNG(imageData.data(), &m_bits, &m_width, &m_height, &m_bitsPerPixel);
    }
    else if (std::strcmp(lowercaseExtension, "jpg") == 0 ||
             std::strcmp(lowercaseExtension, "jpeg") == 0)
    {
        //DecodeJPG(filePath.c_str(), &m_bits, &m_width, &m_height, &m_bitsPerPixel);
    }
    else if (std::strcmp(lowercaseExtension, "bmp") == 0)
    {
        DecodeBMP(imageData.data(), &m_bits, &m_width, &m_height, &m_bitsPerPixel);
    }
}                   

const std::vector<uint8_t>& Bitmap::GetBits() const
{
    return m_bits;
}

int32_t Bitmap::GetBitsPerPixel() const
{
    return m_bitsPerPixel;
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