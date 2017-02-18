#include "PrecompiledHeader.h"
#include "Object.h"

namespace tgon
{

Object::~Object() = default;

//std::shared_ptr<Object> Object::Clone()
//{
//    return std::make_shared<Object>(this);
//}

bool Object::Equals(const Object& rhs) const noexcept
{
    return rhs.GetHashCode() == this->GetHashCode();
}

} /*namespace tgon*/