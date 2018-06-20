#include "PrecompiledHeader.h"

#include "ICloneable.h"

namespace tgon
{

std::shared_ptr<const ICloneable> ICloneable::Clone() const
{
    return const_cast<ICloneable*>(this)->Clone();
}

} /* namespace tgon */