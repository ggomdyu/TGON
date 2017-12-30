"                                           \n\
uniform mat4 g_uWVP;                        \n\
uniform vec4 g_uColor;                      \n\
                                            \n\
attribute vec4 g_aPosition;                 \n\
varying vec4 g_vColor;                      \n\
                                            \n\
void main()                                 \n\
{                                           \n\
    gl_Position = g_uWVP * g_aPosition;     \n\
    g_vColor = g_uColor;                    \n\
}                                           \n\
";