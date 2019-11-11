/**
 * @file    Image.h
 * @author  ggomdyu
 * @since   01/20/2018
 */

#pragma once
#include <vector>
#include <string_view>
#include <algorithm>
#include <memory>

#include "Platform/Config.h"
#include "Math/Extent.h"

namespace tgon
{

enum class ImageFormat
{
    Unknown = 0,
    Bmp,
    Jpg,
    Jpeg = Jpg,
    Png,
    Tiff,
    Gif,
    WebP,
};

enum class PixelFormat
{
    Unknown = 0,
    RGBA8888,
    RGB888,
    RGBA4444,
    R8,
};

class TGON_API Image
{
/**@section Constructor */
public:
    Image() noexcept = default;
    explicit Image(const char* filePath);
    Image(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    Image(Image&& rhs) noexcept;

/**@section Operator */
public:
    Image& operator=(Image&& rhs) noexcept;
    std::byte& operator[](size_t index) noexcept;
    std::byte operator[](size_t index) const noexcept;

/**@section Method */
public:
    void SetData(std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat);
    std::byte* GetData() noexcept;
    const std::byte* GetData() const noexcept;
    const I32Extent2D& GetSize() const noexcept;
    int32_t GetChannels() const noexcept;
    PixelFormat GetPixelFormat() const noexcept;
    bool SaveAsPng(const char* destFilePath) const;
    bool SaveAsJpeg(const char* destFilePath, int32_t quality) const;
    bool SaveAsBmp(const char* destFilePath) const;
    bool SaveAsTga(const char* destFilePath) const;
    
private:
    void LoadImageData(const char* filePath);
    void LoadImageData(const std::byte* fileData, int32_t fileDataBytes);

/**@section Variable */
private:
    std::unique_ptr<std::byte[]> m_imageData;
    I32Extent2D m_size;
    PixelFormat m_pixelFormat = PixelFormat::RGBA8888;
};

} /* namespace tgon */
