/**
 * @file    OpenGLIndexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <GL/glew.h>

namespace tgon
{

class IndexBufferImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    IndexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage);

/* @section Public destructor */
public:
    ~IndexBufferImpl();

/* @section Public method */
public:
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
    std::size_t GetDataBytes() const noexcept;
    
    void Use();
    
    void Unuse();
    
    bool IsValid() const noexcept;
    
    bool IsDynamicUsage() const noexcept;

/* @section Private method */
private:
    GLuint CreateIndexBufferHandle() const;

/* @section Private variable */
private:
    std::size_t m_dataBytes;
    bool m_isDynamicUsage;
    GLuint m_indexBufferHandle;
};

} /* namespace tgon */
