/**
 * @filename    FVF.h
 * @author      ggomdyu
 * @since       03/15/2018
 * @brief
 */

#pragma once
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"

namespace tgon
{

struct V3F_C2F
{
    Vector3 position;
    Vector2 color;
};

struct V3F_T2F
{
    Vector3 position;
    Vector2 uv;
};

struct V3F_N3F_T2F
{
    Vector3 position;
    Vector3 normal;
    Vector2 uv;
};

} /* namespace tgon */