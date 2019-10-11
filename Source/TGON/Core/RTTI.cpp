#include "PrecompiledHeader.h"

#include "RTTI.h"

namespace tgon
{

RTTI::RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept :
    m_typeInfo(&typeInfo),
    m_superRTTI(superRTTI)
{
}

uint32_t RTTI::GetHashCode() const noexcept
{
    return m_typeInfo->hash_code();
}

const char* RTTI::GetName() const noexcept
{
    return m_typeInfo->name();
}

const RTTI* RTTI::GetSuperRTTI() const noexcept
{
    return m_superRTTI;
}

bool RTTI::operator==(const RTTI& rhs) const noexcept
{
    return m_typeInfo == rhs.m_typeInfo;
}

bool RTTI::operator!=(const RTTI& rhs) const noexcept
{
    return !(*this == rhs);
}

bool RTTI::operator<(const RTTI& rhs) const noexcept
{
    return m_typeInfo->before(*rhs.m_typeInfo);
}

bool RTTI::operator>=(const RTTI& rhs) const noexcept
{
    return !(*this < rhs);
}

bool RTTI::operator>(const RTTI& rhs) const noexcept
{
    return (rhs < *this);
}

bool RTTI::operator<=(const RTTI& rhs) const noexcept
{
    return !(*this > rhs);
}

} /* namespace tgon */
