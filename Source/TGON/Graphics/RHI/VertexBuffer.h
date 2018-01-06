/**
 * @filename    VertexBuffer.h
 * @author      ggomdyu
 * @since       01/05/2018
 * @brief
 */

#pragma once
#include <cstdint>

namespace tgon
{
namespace graphics
{

class VertexBuffer
{
public:
    std::size_t GetBufferSize() const;

    void* GetRawBuffer();
    const void* GetRawBuffer() const;

private:
    std::size_t m_bufferSize;
    void* m_buffer;
};

} /* namespace graphics */
} /* namespace tgon */