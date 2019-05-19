/**
 * @file    IEquatable.h
 * @author  ggomdyu
 * @since   05/19/2019
 * @brief   Interface class to compare two instances.
 */

#pragma once
#include <memory>

namespace tgon
{

template <typename _DerivedType>
class IEquatable
{
/**@section Destructor */
public:
    virtual ~IEquatable() = default;

/**@section Operator */
public:
    bool operator==(const _DerivedType& rhs) const noexcept;
    bool operator!=(const _DerivedType& rhs) const noexcept;
    
/**@section Method */
protected:
    virtual bool Equals(const _DerivedType& rhs) = 0;
};

template <typename _DerivedType>
inline bool IEquatable::operator==(const _DerivedType& rhs) const noexcept
{
    return this->Equals(rhs);
}

template <typename _DerivedType>
inline bool IEquatable::operator!=(const _DerivedType& rhs) const noexcept
{
    return !this->Equals(rhs);
}

} /* namespace tgon */
