#pragma once

#include <memory>

namespace tg
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

}
