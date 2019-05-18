/**
 * @file    OpenGLShaderCode.h
 * @author  ggomdyu
 * @since   12/19/2017
 */

#pragma once

constexpr const char g_positionColorVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 g_vertPosition;                                        \n\
                                                                                    \n\
uniform mat4 g_matWVP;                                                              \n\
uniform vec4 g_uColor;                                                              \n\
out vec4 g_fragColor;                                                               \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = g_matWVP * vec4(g_vertPosition, 1.0);                             \n\
    g_fragColor = g_uColor;                                                         \n\
}                                                                                   \n\
";

constexpr const char g_positionColorFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec4 g_fragColor;                                                                \n\
out vec4 g_outColor;                                                                \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    g_outColor = g_fragColor;                                                       \n\
}                                                                                   \n\
";

constexpr const char g_positionNormalUVVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 g_vertPosition;                                        \n\
layout(location = 1) in vec3 g_vertNormal;                                          \n\
layout(location = 2) in vec2 g_vertUV;                                              \n\
out vec2 g_fragUV;                                                                  \n\
uniform mat4 g_matWVP;                                                              \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = g_matWVP * vec4(g_vertPosition, 1.0);                             \n\
    g_fragUV = g_vertUV;                                                            \n\
}                                                                                   \n\
";

constexpr const char g_positionNormalUVFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 g_fragUV;                                                                   \n\
out vec4 g_outColor;                                                                \n\
                                                                                    \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    g_outColor = texture(textureSampler, g_fragUV);                                 \n\
}                                                                                   \n\
";

constexpr const char g_positionUVVert[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
layout(location = 0) in vec3 g_vertPosition;                                        \n\
layout(location = 1) in vec2 g_vertUV;                                              \n\
uniform mat4 g_matWVP;                                                              \n\
out vec2 g_fragUV;                                                                  \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = g_matWVP * vec4(g_vertPosition, 1.0);                             \n\
    g_fragUV = g_vertUV;                                                            \n\
}                                                                                   \n\
";

constexpr const char g_positionUVFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 g_fragUV;                                                                   \n\
out vec4 g_outColor;                                                                \n\
                                                                                    \n\
uniform sampler2D textureSampler;                                                   \n\
uniform vec4 g_blendColor;                                                          \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    g_outColor = texture(textureSampler, g_fragUV) * g_blendColor;                  \n\
}                                                                                   \n\
";

constexpr const char g_grayScaleTextureFrag[] =
"                                                                                   \n\
#version 330 core                                                                   \n\
                                                                                    \n\
in vec2 g_fragUV;                                                                   \n\
out vec4 g_outColor;                                                                \n\
uniform vec4 g_uColor;                                                              \n\
uniform sampler2D textureSampler;                                                   \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    vec4 color = texture(textureSampler, g_fragUV);                                 \n\
    float grayScale = (color.r + color.g + color.b) / 3;                            \n\
    g_outColor = vec4(grayScale, grayScale, grayScale, color.a) * g_uColor;         \n\
}                                                                                   \n\
";
