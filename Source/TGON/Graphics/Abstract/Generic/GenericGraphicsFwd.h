/**
 * @filename    GenericGraphicsFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once

namespace tgon
{
namespace core
{

struct Color4f;
struct Color3b;
struct Vector2;
struct Vector3;
struct Matrix4x4;

template <typename _ValueType>
struct BasicRect;

using FRect = BasicRect<float>;

} /* namespace core */

namespace graphics
{

enum class FillMode;
enum class CullMode;
enum class PrimitiveType;
class VertexBuffer;
struct VertexBufferDesc;

} /* namespace graphics */
} /* namespace tgon */