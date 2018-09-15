/**
 * @file    IndexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <initializer_list>

#include "Core/Platform/Config.h"

#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLIndexBuffer.h"
#endif

namespace tgon
{
    
class TGON_API IndexBuffer final :
    private boost::noncopyable
{
/**@section Public constructor */
public:
    /**
     * @brief                       Initializes the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    template <typename _DataArrayType, std::size_t _DataArraySize>
    IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    
    /**
     * @brief                       Initializes the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    IndexBuffer(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
/**@section Public method */
public:
    /**
     * @brief                       Sets the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    template <typename _DataArrayType, std::size_t _DataArraySize>
    void SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage);
    
    /**
     * @brief                       Sets the index buffer with the specified data.
     * @param [in] data             The data to store in the index buffer.
     * @param [in] dataBytes        The byte size of the data.
     * @param [in] isDynamicUsage   If true, then the index buffer will not be modified after set.
     */
    void SetData(const void* data, std::size_t dataBytes, bool isDynamicUsage);
    
    /**@brief                       Gets the size of the stored index buffer.  */
    std::size_t GetDataBytes() const noexcept;
    
    /**@brief                       Sets the rendering pipeline to choose this buffer. */
    void Use();
    
    /**@brief                       Sets the rendering pipeline does not choose this buffer. */
    void Unuse();
    
    /**
     * @brief                       Checks the index buffer was created successfully.
     * @return                      Returns true if the buffer was created successfully, false otherwise.
     */
    bool IsValid() const noexcept;
    
    bool IsDynamicUsage() const noexcept;

/**@section Private variable */
public:
    IndexBufferImpl m_indexBufferImpl;
};
    
template <typename _DataArrayType, std::size_t _DataArraySize>
inline IndexBuffer::IndexBuffer(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage) :
    IndexBuffer(data, sizeof(data), isDynamicUsage)
{
}

template <typename _DataArrayType, std::size_t _DataArraySize>
inline void IndexBuffer::SetData(const _DataArrayType(&data)[_DataArraySize], bool isDynamicUsage)
{
    this->SetData(data, sizeof(data), isDynamicUsage);
}

} /* namespace tgon */
