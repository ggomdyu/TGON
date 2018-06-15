/**
 * @filename    IComparable.h
 * @author      ggomdyu
 * @since       04/07/2018
 */

#pragma once
#include <cstdint>

namespace tgon
{

class IComparable
{
/* @section Public destructor */
public:
    virtual ~IComparable() = default;

/* @section Public method */
public:
    /**
     * @brief   Compares this instance with another instance of the same type.
     * @return  A value that indicates whether this instance precedes.
     *          Less than Zero: This instance precedes obj.
     *          Zero: This instance has same sort order with obj.
     *          Greather than Zero: This instance follows obj.
     */
    virtual int32_t CompareTo(IComparable* obj) const = 0;
};

} /* namespace tgon */
