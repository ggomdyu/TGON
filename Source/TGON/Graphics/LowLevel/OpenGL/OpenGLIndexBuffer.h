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
    /**
     * @brief                       Initializes the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    IndexBufferImpl(const void* data, std::size_t dataBytes, bool isDynamicUsage);

/* @section Public destructor */
public:
    ~IndexBufferImpl();

/* @section Public method */
public:
    /**
     * @brief                       Sets the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
    /* @brief                       Gets the size of the stored index buffer.  */
    std::size_t GetDataBytes() const noexcept;
    
    /* @brief                       Sets the rendering pipeline to choose this buffer. */
    void Use();
    
    /* @brief                       Sets the rendering pipeline does not choose this buffer. */
    void Unuse();
    
    /**
     * @brief                       Checks the index buffer was created successfully.
     * @return                      Returns true if the buffer was created successfully, false otherwise.
     */
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
