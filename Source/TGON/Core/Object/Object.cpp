#include "PrecompiledHeader.pch"

#include "Object.h"

namespace tgon
{
namespace object
{

TypeInfo::TypeInfo(const std::type_info& rawTypeInfo, const TypeInfo* superTypeInfo) noexcept :
    m_rawTypeInfo(rawTypeInfo),
    m_superTypeInfo(superTypeInfo)
{
}

std::size_t TypeInfo::GetHashCode() const noexcept
{
    return m_rawTypeInfo.hash_code();
}

const char* TypeInfo::GetName() const noexcept
{
    return m_rawTypeInfo.name();
}

const TypeInfo* TypeInfo::GetSuperTypeInfo() const noexcept
{
    return m_superTypeInfo;
}


std::shared_ptr<Object> Object::Clone() const
{
    return nullptr;
}

} /* namespace object */
} /* namespace tgon */
