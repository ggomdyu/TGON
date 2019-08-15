/**
 * @file    TextureType.h
 * @author  ggomdyu
 * @since   06/30/2018
 */

#pragma once

namespace tgon
{

enum class FilterMode
{
    Point,
    Bilinear,
};

enum class WrapMode
{
    Repeat,
    Clamp,
    Mirror,
};

}
