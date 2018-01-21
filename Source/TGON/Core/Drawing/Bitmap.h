/**
 * @filename    Bitmap.h
 * @author      ggomdyu
 * @since       01/20/2018
 */

#pragma once
#include "Core/Platform/Config.h"

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
    explicit Bitmap(const uint8_t* bits, ImageFormat);
};

} /* namespace core */
} /* namespace tgon */
