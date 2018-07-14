/**
 * @file    OpenGLShader.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

namespace tgon
{
    
class RenderTargetImpl;

class RenderTarget final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    RenderTarget(int32_t width, int32_t height, int32_t multisampleLevel);
    
/* @section Public destructor */
public:
    ~RenderTarget() = default;
    
/* @section Public method */
public:
    void Use();
    void Unuse();
    
/* @section Private variable */
private:
    std::unique_ptr<RenderTargetImpl> m_renderTargetImpl;
};

} /* namespace tgon */
