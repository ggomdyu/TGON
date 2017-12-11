#include "PrecompiledHeader.pch"
#include "TextureUtility.h"

#include <boost/filesystem/fstream.hpp>
#include <cstdint>
#include <stdio.h>
#include <png.h>

namespace tgon
{
namespace render
{

bool LoadPNG(const char* filePath, std::vector<uint8_t>* destBuffer, std::size_t* width, std::size_t* height)
{
    bool succeed = false;

    FILE* file = fopen(filePath, "rb");
    {
        do
        {
            if (file == nullptr)
            {
                break;
            }

            // Reserve the vector by file size.
            fseek(file, 0, SEEK_END);
            long fileSize = ftell(file);
            destBuffer.reserve(fileSize);

            // Read file and assign to the vector.
            fread(destBuffer.data(), 0, fileSize, file);

            // Check file is PNG.
            bool isFilePNG = !png_sig_cmp(destBuffer.data(), 0, 8);
            if (isFilePNG == false)
            {
                break;
            }

            // We will pass pointers to error handling functions, and a pointer to a data struct for use by the error functions, if necessary (the pointer and functions can be NULL if the default error handlers are to be used).
            png_structp pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            if (pngStruct == nullptr)
            {
                break;
            }

            png_infop pngInfo = png_create_info_struct(pngStruct);
            if (pngInfo == nullptr)
            {
                png_destroy_read_struct(&pngStruct, nullptr, nullptr);
                break;
            }

            // Set error handling with setjmp.
            // Unless if you set up your own error handlers in the png_create_read_struct earlier.
            if (setjmp(png_jmpbuf(pngStruct)))
            {
                png_destroy_read_struct(&pngStruct, &pngInfo, nullptr);
                break;
            }

            // Set up the output control. The default for libpng is to use the C function fread().
            // If you use this, you will need to pass a valid FILE * in the function png_init_io().
            png_init_io(pngStruct, file);

            // If you had previously opened the file and read any of the signature from the beginning in order to see if this was a PNG file,
            // you need to let libpng know that there are some bytes missing from the start of the file.
            png_set_sig_bytes(pngStruct, 8);



            succeed = true;
        }
        while (false);

    }
    fclose(file);

    return succeed;
}

} /* namespace render */
} /* namespace tgon */
