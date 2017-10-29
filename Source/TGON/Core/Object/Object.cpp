#include "PrecompiledHeader.pch"
#include "Object.h"

namespace tgon
{
namespace object
{

std::shared_ptr<ICloneable> Object::Clone() const
{
    return std::make_shared<Object>();
}

} /* namespace object */
} /* namespace tgon */
