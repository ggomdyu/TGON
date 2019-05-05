/**
 * @file    OpenGLIndexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <GL/glew.h>

#include "Core/Platform/Config.h"

namespace tgon
{

class TGON_API OpenGLIndexBuffer :
    private boost::noncopyable
{
/**@section Constructor */
public:
    /**
     * @brief                       Initializes the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    OpenGLIndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage);

/**@section Destructor */
public:
    ~OpenGLIndexBuffer();

/**@section Method */
public:
    /**
     * @brief                       Sets the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
    /**@brief   Gets the byte size of the data stored in the buffer.  */
    std::size_t GetDataBytes() const noexcept;
    
    /**@brief   Sets the rendering pipeline to use this buffer. */
    void Use();
    
    /**@brief   Sets the rendering pipeline does not use this buffer. */
    void Unuse();
    
    /**
     * @brief   Checks the buffer was created successfully.
     * @return  Returns true if the buffer was created successfully, false otherwise.
     */
    bool IsValid() const noexcept;
    
    bool IsDynamicUsage() const noexcept;

private:
    GLuint CreateIndexBufferHandle() const;

/**@section Variable */
private:
    std::size_t m_dataBytes;
    bool m_isDynamicUsage;
    GLuint m_indexBufferHandle;
};
    
using PlatformIndexBuffer = OpenGLIndexBuffer;

} /* namespace tgon */
