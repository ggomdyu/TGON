"\
uniform mat4 g_uWVP;\
uniform vec4 g_uColor;\
\
attribute vec4 g_aPosition;\
varying vec4 g_vColor;\
\
void main()\
{\
    gl_Position = g_uWVP * g_aPosition;\
    g_vColor = g_uColor;\
}\
";
