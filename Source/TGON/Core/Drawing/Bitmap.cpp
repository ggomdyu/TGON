#include "PrecompiledHeader.pch"

#include "Bitmap.h"

//#include <boost/filesystem/fstream.hpp>
#include <cstdint>
#include <png.h>

namespace tgon
{
namespace core
{

bool DecodePNG(const char* filePath, std::vector<uint8_t>* bits, int32_t* width, int32_t* height, int32_t* depthBits)
{
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
    if (file == nullptr)
    {
        return false;
    }

    // Resize the vector by file size.
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    bits->resize(fileSize);

    // Read the file and assign to the vector.
    fread(&bits[0], 0, fileSize, file);

    // Check whether the file format is PNG or not.
    bool isPNGFormat = !png_sig_cmp(&(*bits)[0], 0, 8);
    if (isPNGFormat == false)
    {
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
    *depthBits = png_get_bit_depth(pngStruct, pngInfo);

    png_uint_32 colorType = png_get_color_type(pngStruct, pngInfo);
    if (colorType == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_palette_to_rgb(pngStruct);
    }
    else if (colorType == PNG_COLOR_TYPE_GRAY && *depthBits < 8)
    {
        png_set_expand_gray_1_2_4_to_8(pngStruct);
    }

    // Expand tRNS chunk data to full alpha channel.
    if (png_get_valid(pngStruct, pngInfo, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(pngStruct);
    }

    if (*depthBits == 16)
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

    // Update information structure.
    png_read_update_info(pngStruct, pngInfo);

    png_byte** pngBytePtr = reinterpret_cast<png_byte**>(operator new(sizeof(png_byte) * (*height)));
    for (int y = 0; y < *height; ++y)
    {
        pngBytePtr[y] = reinterpret_cast<png_byte*>(operator new(png_get_rowbytes(pngStruct, pngInfo)));
    }

    png_read_image(pngStruct, pngBytePtr);

    png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
}
    
Bitmap::Bitmap(const std::string& filePath)
{
    const char* extension = filePath.c_str() + filePath.rfind('.');

    int n = 3;
}

const std::vector<uint8_t>& Bitmap::GetBits() const
{
    return m_bits;
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