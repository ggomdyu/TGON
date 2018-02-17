/**
 * @filename    OpenGLIndexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 */

#pragma once
#include "../Generic/GenericIndexBuffer.h"

#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

class OpenGLIndexBuffer :
    public GenericIndexBuffer
{
/* @section Public constructor */
public:
    template <typename _DataArrayType, std::size_t _DataArraySize>
    OpenGLIndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    OpenGLIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    virtual ~OpenGLIndexBuffer();

/* @section Public method */
public:
    virtual void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage) final override;

    virtual void Use() final override;    
    virtual void Unuse() final override;

    virtual bool IsValid() const noexcept final override;

/* @section Private method */
private:
    GLuint GenerateBuffer() const;

/* @section Private variable */
private:
    GLuint m_indexBufferHandle;
};

template<typename _DataArrayType, std::size_t _DataArraySize>
inline OpenGLIndexBuffer::OpenGLIndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage) :
    OpenGLIndexBuffer(data, sizeof(data), isDynamicUsage)
{
}

class IndexBuffer : public OpenGLIndexBuffer
{
/* @section Public constructor */
public:
    using OpenGLIndexBuffer::OpenGLIndexBuffer;
};

} /* namespace graphics */
} /* namespace tgon */