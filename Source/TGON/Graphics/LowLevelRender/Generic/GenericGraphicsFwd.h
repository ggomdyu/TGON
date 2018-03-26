/**
 * @filename    GenericGraphicsFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once

namespace tgon
{

struct Color4f;
struct Color3b;
struct Vector2;
struct Vector3;
struct Matrix4x4;
template <typename _ValueType>
struct BasicRect;
using FRect = BasicRect<float>;
enum class FillMode;
enum class CullMode;
enum class PrimitiveType;
class GenericVertexBuffer;
class GenericIndexBuffer;
class GenericTexture;
class GenericShader;
struct VertexBufferDesc;

} /* namespace tgon */