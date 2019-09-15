/**
 * @file    OpenGLIndexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <GL/glew.h>
#include <cstdint>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class TGON_API OpenGLIndexBuffer :
    private NonCopyable
{
/**@section Constructor */
public:
    OpenGLIndexBuffer();
    OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) noexcept;

/**@section Destructor */
public:
    ~OpenGLIndexBuffer();
    
/**@section Operator */
public:
    OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&& rhs) noexcept;

/**@section Method */
public:
    void SetData(const void* data, int32_t dataBytes, bool isDynamicUsage);
    int32_t GetDataBytes() const noexcept;
    void Use();
    void Unuse();
    bool IsValid() const noexcept;
    bool IsDynamicUsage() const noexcept;

private:
    GLuint CreateIndexBufferHandle() const;
    void Destroy();

/**@section Variable */
private:
    int32_t m_dataBytes;
    bool m_isDynamicUsage;
    GLuint m_indexBufferHandle;
};
    
using PlatformIndexBuffer = OpenGLIndexBuffer;

} /* namespace tgon */
