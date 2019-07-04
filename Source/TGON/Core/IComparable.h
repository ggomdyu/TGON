/**
 * @file    IComparable.h
 * @author  ggomdyu
 * @since   04/07/2018
 * @brief   Interface class to compare two instances.
 */

#pragma once
#include <cstdint>

namespace tgon
{

class IComparable
{
/**@section Destructor */
public:
    virtual ~IComparable() = default;

/**@section Operator */
public:
    bool operator==(const IEquatable* rhs) const
    {
        return this->Equals(rhs);
    }
    
    bool operator!=(const IEquatable* rhs) const
    {
        return !this->Equals(rhs);
    }
    
/**@section Method */
public:
    virtual bool Equals(const IComparable* rhs) const
    {
        return this->CompareTo(rhs) == 0;
    }
    
    /**
     * @brief   Compares this instance with another instance of the same type.
     * @return  A value that indicates whether this instance precedes.
     *          Less than Zero: This instance precedes rhs.
     *          Zero: This instance has same sort order with rhs.
     *          Greather than Zero: This instance follows rhs.
     */
    virtual int32_t CompareTo(const IComparable* rhs) const = 0;
};

} /* namespace tgon */
