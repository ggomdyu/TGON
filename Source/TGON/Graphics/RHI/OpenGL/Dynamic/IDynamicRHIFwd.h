/**
 * @filename    IDynamicRHIFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once

namespace tgon
{
namespace math
{

struct Color4f;
struct Color3b;
struct Vector2;
struct Vector3;
struct Matrix4x4;

template <typename _ValueType>
struct BasicRect;

using FRect = BasicRect<float>;

} /* namespace math */
} /* namespace tgon */