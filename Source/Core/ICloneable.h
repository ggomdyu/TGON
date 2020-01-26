/**
 * @file    ICloneable.h
 * @author  ggomdyu
 * @since   10/28/2017
 * @brief   Interface class for virtual copy constructor.
 */

#pragma once
#include <memory>

namespace tgon
{

class ICloneable
{
/**@section Destructor */
public:
    virtual ~ICloneable() = default;

/**@section Method */
public:
    virtual std::shared_ptr<ICloneable> Clone() = 0;
    std::shared_ptr<const ICloneable> Clone() const;
};
    
inline std::shared_ptr<const ICloneable> ICloneable::Clone() const
{
    return const_cast<ICloneable*>(this)->Clone();
}

} /* namespace tgon */
