/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

#include "Graphics/RHI/Base/BaseRHI.h"

#include "OpenGLRHIFwd.h"

namespace tgon
{
namespace rhi
{
namespace gl
{

class OpenGLRHI :
    public BaseRHI
{
/* @section Public constructor */
public:
    explicit OpenGLRHI(const VideoMode& videoMode);

/* @section Public method */
public:
    virtual void BeginScene(PrimitiveType primitiveType) override;
    virtual void EndScene() override;
    virtual void Flush() override;

/* @section Private method */
private:
    std::shared_ptr<OpenGLContext> MakeContext(const VideoMode& videoMode) const;

/* @section Private variable */
private:
    std::shared_ptr<OpenGLContext> m_context;
};

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */
