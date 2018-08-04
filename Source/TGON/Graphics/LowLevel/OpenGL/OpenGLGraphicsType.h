/**
 * @filename    OpenGLGraphicsType.h
 * @author      ggomdyu
 * @since       06/06/2018
 */

#pragma once
#include <GL/glew.h>

namespace tgon
{

enum class PrimitiveType
{
    Points = GL_POINTS,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    TriangleFan = GL_TRIANGLE_FAN,
};

enum class FillMode
{
    Point = GL_POINT,
    WireFrame = GL_LINE,
    Solid = GL_FILL,
};

enum class CullMode
{
    CW = GL_CW,
    CCW = GL_CCW,
};
    
enum class BlendMode
{
    Normal,
    Darken,
    Multiply,
    Divide,
    Subtract,
    SoftLight,
    HardLight,
};

} /* namespace tgon */
