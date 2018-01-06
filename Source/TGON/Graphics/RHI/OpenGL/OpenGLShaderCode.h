/**
 * @filename    OpenGLShaderCode.h
 * @author      ggomdyu
 * @since       12/19/2017
 */

#pragma once

constexpr const char g_positionColorVert[] =
"                                           \n\
uniform mat4 g_uWVP;                        \n\
uniform vec4 g_uColor;                      \n\
                                            \n\
in vec4 g_inPosition;                        \n\
out vec4 g_outColor;                          \n\
                                            \n\
void main()                                 \n\
{                                           \n\
    gl_Position = g_uWVP * g_aPosition;     \n\
    g_vColor = g_uColor;                    \n\
}                                           \n\
";

constexpr const char g_positionColorFrag[] =
"                               \n\
in vec4 g_vColor;          \n\
                                \n\
void main()                     \n\
{                               \n\
    gl_FragColor = g_vColor;    \n\
}                               \n\
";
