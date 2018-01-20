/**
 * @filename    InstantiateCounter.h
 * @author      ggomdyu
 * @since       09/24/2017
 * @brief       Set of functions to manage/limit the count of object instantiation.
 */

#pragma once
#include <type_traits>
#include <cassert>

namespace tgon
{
namespace core
{

/**
 * @class   InstantiateCounter
 * @brief   Counts the number of specified type's instantiation.
 */
template <typename _ClassType>
class InstantiateCounter
{
/* @section Protected constructor */
protected:
    InstantiateCounter() noexcept;

/* @section Public method */
public:
    static uint32_t GetInstantiatedCount() noexcept;

/* @section Protected variable */
protected:
    static uint32_t ms_instantiatedCount;
};

template <typename _ClassType>
uint32_t InstantiateCounter<_ClassType>::ms_instantiatedCount = 0;

template <typename _ClassType>
inline InstantiateCounter<_ClassType>::InstantiateCounter() noexcept
{
    ++ms_instantiatedCount;
}

template <typename _ClassType>
inline uint32_t InstantiateCounter<_ClassType>::GetInstantiatedCount() noexcept
{
    return ms_instantiatedCount;
}

/**
 * @class   InstanceCounter
 * @brief   Counts the number of specified type's instance.
 */
template <typename _ClassType>
class InstanceCounter :
    private InstantiateCounter<_ClassType>
{
public:
    ~InstanceCounter();

public:
    static uint32_t GetInstanceCount() noexcept;
};

template<typename _ClassType>
inline InstanceCounter<_ClassType>::~InstanceCounter()
{
    --InstantiateCounter<_ClassType>::ms_instantiatedCount;
}

template<typename _ClassType>
inline uint32_t InstanceCounter<_ClassType>::GetInstanceCount() noexcept
{
    return InstantiateCounter<_ClassType>::ms_instantiatedCount;
}

/**
 * @class   InstantiateCountLimiter
 * @brief   Restricts the instantiation count of the specified type.
 */
template <typename _ClassType, uint32_t _MaxInstantiationCount>
class InstantiateCountLimiter :
    private InstantiateCounter<_ClassType>
{
/* @section Protected constructor */
protected:
    InstantiateCountLimiter();
};

template <typename _ClassType, uint32_t _MaxInstantiationCount>
inline InstantiateCountLimiter<_ClassType, _MaxInstantiationCount>::InstantiateCountLimiter()
{
    assert(InstantiateCounter<_ClassType>::GetInstantiatedCount() <= _MaxInstantiationCount && "The object has been instantiated more than the specified number.");
}

/**
 * @class   InstanceCountLimiter
 * @brief   Restricts the instance count of the specified type.
 */
template <typename _ClassType, uint32_t _MaxInstanceCount>
class InstanceCountLimiter :
    private InstantiateCountLimiter<_ClassType, _MaxInstanceCount>
{
/* @section Protected constructor */
protected:
    InstanceCountLimiter() = default;

/* @section Public destructor */
public:
    ~InstanceCountLimiter();
};

template <typename _ClassType, uint32_t _MaxInstanceCount>
inline InstanceCountLimiter<_ClassType, _MaxInstanceCount>::~InstanceCountLimiter()
{
    --InstantiateCounter<_ClassType>::ms_instantiatedCount;
}

} /* namespace core */
} /* namespace tgon */
