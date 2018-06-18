/**
 * @file    Graphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/preprocessor/cat.hpp>

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLGraphics.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/Direct3D11Graphics.h"
#endif

#include "GraphicsConfig.h"

namespace tgon
{

class Graphics :
    public BOOST_PP_CAT(TGON_GRAPHICS_NAME, Graphics)
{
public:
    TGON_RUNTIME_OBJECT(Graphics);

/* @section Public constructor */
public:
    using SuperType::SuperType;
};

} /* namespace tgon */
