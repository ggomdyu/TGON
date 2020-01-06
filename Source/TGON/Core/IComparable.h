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
    bool operator==(const IComparable* rhs) const;
    bool operator!=(const IComparable* rhs) const;
    
/**@section Method */
public:
    virtual bool Equals(const IComparable* rhs) const;
    virtual int32_t CompareTo(const IComparable* rhs) const = 0;
};
    
inline bool IComparable::operator==(const IComparable* rhs) const
{
    return this->Equals(rhs);
}
    
inline bool IComparable::operator!=(const IComparable* rhs) const
{
    return !this->Equals(rhs);
}

inline bool IComparable::Equals(const IComparable* rhs) const
{
    return this->CompareTo(rhs) == 0;
}

} /* namespace tgon */
