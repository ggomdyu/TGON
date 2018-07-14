/**
 * @file    OpenGLShader.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <GL/glew.h>

namespace tgon
{

class RenderTargetImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    RenderTargetImpl(int32_t width, int32_t height, int32_t multisampleLevel);
    
public:
    ~RenderTargetImpl();
    
/* @section Public method */
public:
    void Use();
    void Unuse();
    
/* @section Private variable */
private:
    int32_t m_width;
    int32_t m_height;
};

} /* namespace tgon */
