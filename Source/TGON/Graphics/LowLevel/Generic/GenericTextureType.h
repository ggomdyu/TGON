/**
 * @filename    GenericTextureType.h
 * @author      ggomdyu
 * @since       03/22/2018
 * @brief
 */

#pragma once

namespace tgon
{

enum class TextureFilterMode
{
    Point = 0,
    Bilinear,
};

enum class TextureWrapMode
{
    Repeat,
    Clamp,
    Mirror,
};

struct TextureCreateDesc
{
    TextureFilterMode filterMode = TextureFilterMode::Bilinear;
    TextureWrapMode wrapMode = TextureWrapMode::Repeat;
    bool isUseMipmap = true;
};

} /* namespace tgon */