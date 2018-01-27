/**
 * @filename    OpenGLShaderCode.h
 * @author      ggomdyu
 * @since       12/19/2017
 */

#pragma once

/**
 * gl_Vertex	        Position (vec4)
 * gl_Normal	        Normal (vec4)
 * gl_Color	            Primary color of vertex (vec4)
 * gl_MultiTexCoord0	Texture coordinate of texture unit 0 (vec4)
 * gl_MultiTexCoord1	Texture coordinate of texture unit 1 (vec4)
 * gl_MultiTexCoord2	Texture coordinate of texture unit 2 (vec4)
 * gl_MultiTexCoord3	Texture coordinate of texture unit 3 (vec4)
 * gl_MultiTexCoord4	Texture coordinate of texture unit 4 (vec4)
 * gl_MultiTexCoord5	Texture coordinate of texture unit 5 (vec4)
 * gl_MultiTexCoord6   Texture coordinate of texture unit 6 (vec4)
 * gl_MultiTexCoord7	Texture coordinate of texture unit 7 (vec4)
 * gl_FogCoord	Fog Coord (float)
 */

constexpr const char g_positionColorVert[] =
"                                                           \n\
#version 330 core                                           \n\
                                                            \n\
layout(location = 0) in vec3 g_vPosition;                   \n\
layout(location = 1) in vec4 g_vColor;                      \n\
                                                            \n\
out vec4 g_fColor;                                          \n\
                                                            \n\
uniform mat4 g_uMVP;                                        \n\
                                                            \n\
void main()                                                 \n\
{                                                           \n\
    gl_Position = g_uMVP * vec4(g_vPosition, 1.0);          \n\
    g_fColor = g_vColor;                                    \n\
}                                                           \n\
";

constexpr const char g_positionColorFrag[] =
"                                                           \n\
#version 330 core                                           \n\
                                                            \n\
in vec4 g_fColor;                                           \n\
out vec4 g_outColor;                                        \n\
                                                            \n\
void main()                                                 \n\
{                                                           \n\
    g_outColor = g_fColor;                                  \n\
}                                                           \n\
";
