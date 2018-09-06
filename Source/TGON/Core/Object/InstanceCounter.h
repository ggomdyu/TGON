/**
 * @file    InstanceCounter.h
 * @author  ggomdyu
 * @since   06/06/2018
 * @brief   Set of functions to manage the count of object instace.
 */

#pragma once
#include <cassert>
#include <cstdint>

namespace tgon
{

template <typename _InstanceType>
class InstanceCounter
{
/* @section Protected constructor */
protected:
    InstanceCounter() noexcept
    {
        ++ms_instanceCount;
    }

/* @section Public destructor */
public:
    ~InstanceCounter() noexcept
    {
        --ms_instanceCount;
    }

/* @section Public method */
public:
    static int32_t GetInstanceCount() noexcept
    {
        return ms_instanceCount;
    }

/* @section Protected variable */
protected:
    static int32_t ms_instanceCount;
};

template <typename _InstanceType>
int32_t InstanceCounter<_InstanceType>::ms_instanceCount = 0;

template <typename _InstanceType, int32_t _MaxInstanceCount>
class InstanceCountLimiter :
    private InstanceCounter<_InstanceType>
{
/* @section Protected constructor */
protected:
    InstanceCountLimiter() noexcept
    {
        assert(InstanceCounter<_InstanceType>::GetInstanceCount() <= _MaxInstanceCount && "The object instance count is more than specified.");
    }
};

} /* namespace tgon */
