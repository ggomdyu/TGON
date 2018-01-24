/**
 * @filename    Bitmap.h
 * @author      ggomdyu
 * @since       01/20/2018
 */

#pragma once
#include "Core/Platform/Config.h"

#include <vector>
#include <cstdint>

namespace tgon
{
namespace core
{

enum class ImageFormat
{
};

class Bitmap
{
public:
    explicit Bitmap(const std::string& filePath);
    explicit Bitmap(const std::string& filePat h);

private:
    std::vector<uint8_t> m_bits;
    int32_t m_width;
    int32_t m_height;
    std::string m_filePath;
};

} /* namespace core */
} /* namespace tgon */
