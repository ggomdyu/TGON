/**
 * @file    InstantiateCounter.h
 * @author  ggomdyu
 * @since   09/24/2017
 * @brief   Set of functions to manage the count of object instantiation.
 */

#pragma once
#include <cassert>
#include <cstdint>

namespace tgon
{

template <typename _InstanceType>
class InstantiateCounter
{
/* @section Protected constructor */
protected:
    InstantiateCounter() noexcept;

/* @section Public method */
public:
    static int32_t GetInstantiateCount() noexcept;

/* @section Protected variable */
protected:
    static int32_t ms_instantiateCount;
};

template <typename _InstanceType>
int32_t InstantiateCounter<_InstanceType>::ms_instantiateCount = 0;

template <typename _InstanceType>
inline InstantiateCounter<_InstanceType>::InstantiateCounter() noexcept
{
    ++ms_instantiateCount;
}

template <typename _InstanceType>
inline int32_t InstantiateCounter<_InstanceType>::GetInstantiateCount() noexcept
{
    return ms_instantiateCount;
}

template <typename _InstanceType, int32_t _MaxInstantiateCount>
class InstantiateCountLimiter :
    private InstantiateCounter<_InstanceType>
{
/* @section Protected constructor */
protected:
    InstantiateCountLimiter() noexcept;
};

template <typename _InstanceType, int32_t _MaxInstantiateCount>
inline InstantiateCountLimiter<_InstanceType, _MaxInstantiateCount>::InstantiateCountLimiter() noexcept :
    InstantiateCounter<_InstanceType>()
{
    assert(InstantiateCounter<_InstanceType>::GetInstantiateCount() <= _MaxInstantiateCount && "The object has been instantiated more than the specified count.");
}

} /* namespace tgon */
