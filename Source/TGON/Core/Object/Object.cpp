#include "PrecompiledHeader.pch"
#include "Object.h"

#include <cassert>

namespace tgon
{
namespace object
{

std::shared_ptr<Object> Object::Clone() const
{
    return nullptr;
}

const TypeInfo& Object::GetStaticType() noexcept
{
    static const TypeInfo typeInfo("tgon::object::Object", nullptr);
    return typeInfo;
}

} /* namespace object */
} /* namespace tgon */
