#include "PrecompiledHeader.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#ifdef _MSC_VER
#   define STBI_MSC_SECURE_CRT
#endif
#include <stb_image.h>

#include "String/StringTraits.h"
#include "String/Hash.h"

#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
#   include "ImageProcessor/BmpImageProcessor.h"
#   include "ImageProcessor/JpgImageProcessor.h"
#   include "ImageProcessor/PngImageProcessor.h"
#endif
#include "ImageProcessor/WebPImageProcessor.h"

#include "ImageUtility.h"

namespace tgon
{

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const char* filePath, int32_t* destWidth, int32_t* destHeight, PixelFormat* destPixelFormat)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
#else
    FILE* file = fopen(filePath, "rb");
#endif
    if (file == nullptr)
    {
        return nullptr;
    }
    
    fseek(file, 0, SEEK_END);
    int32_t fileSize = static_cast<int32_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    auto fileData = std::make_unique<uint8_t[]>(fileSize);
    fread(fileData.get(), 1, fileSize, file);
    fclose(file);

    return LoadImageData(fileData.get(), fileSize, destWidth, destHeight, destPixelFormat);
}

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const uint8_t* fileData, int32_t fileDataBytes, int32_t* destWidth, int32_t* destHeight, PixelFormat* destPixelFormat)
{
#if TGON_USE_LOWLEVEL_IMAGE_IMPORTER
    auto loadImage = [&](auto& imageProcessor)
    {
        *destWidth = imageProcessor.GetWidth();
        *destHeight = imageProcessor.GetHeight();
        *destChannels = imageProcessor.GetChannels();

        return std::move(imageProcessor.GetImageData());
    };

    if (PngImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(PngImageProcessor(fileData, fileDataBytes));
    }
    else if (JpgImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(JpgImageProcessor(fileData, fileDataBytes));
    }
    else if (BmpImageProcessor::VerifyFormat(fileData, fileDataBytes))
    {
        return loadImage(BmpImageProcessor(fileData, fileDataBytes));
    }
#else
    *destPixelFormat = PixelFormat::RGBA8888;
#endif

    return std::unique_ptr<uint8_t[]>(stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(fileData), fileDataBytes, destWidth, destHeight, nullptr, STBI_rgb_alpha));
}

TGON_API ImageFormat ConvertStringToImageFormat(const std::string_view& str)
{
    char lowercaseStr[32]{};
    BasicStringTraits<char>::ToLower(str, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

    switch (X65599Hash(lowercaseStr))
    {
    case TGON_X65599("bmp"):
        return ImageFormat::Bmp;
    case TGON_X65599("jpg"):
        return ImageFormat::Jpg;
    case TGON_X65599("jpeg"):
        return ImageFormat::Jpeg;
    case TGON_X65599("png"):
        return ImageFormat::Png;
    case TGON_X65599("tiff"):
        return ImageFormat::Tiff;
    case TGON_X65599("gif"):
        return ImageFormat::Gif;
    case TGON_X65599("webp"):
        return ImageFormat::WebP;
    default:
        return ImageFormat::Unknown;
    }
}

} /* namespace tgon */
