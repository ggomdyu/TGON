/**
 * @filename    GenericBuffer.h
 * @author      ggomdyu
 * @since       07/03/2017
 */

#include <cstdint>

namespace tgon
{
namespace graphics
{

struct BufferCreateDescription
{
    uint32_t bufferSize;
};

template <typename _DerivedType>
class GenericBuffer
{
/* @section Ctor/Dtor */
public:
    
/* @section Public method */
public:
    /* @brief Get buffer which is independent type. */
    void* GetBuffer() { return static_cast<_DerivedType*>(this)->GetBuffer(); }

    /* @brief Get allocated size of buffer. */
    uint32_t GetBufferSize() const { static_cast<_DerivedType*>(this)->GetBufferSize(); };

// @section Private variable
public:
};

} /* namespace graphics */
} /* namespace tgon */
