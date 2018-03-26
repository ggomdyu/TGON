/**
 * @filename    RTTI.h
 * @author      ggomdyu
 * @since       10/29/2017
 */

#pragma once
#include <typeinfo>
#include <cstdint>

namespace tgon
{

struct RTTI final
{
/* @section Public constructor */
public:
    RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept;

/* @section Public method */
public:
    std::size_t GetHashCode() const noexcept;
    const char* GetName() const noexcept;

    const RTTI* GetSuperRTTI() const noexcept;

/* @section Private variable */
private:
    const std::type_info& m_typeInfo;
    const RTTI* m_superRTTI;
};

inline RTTI::RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept :
    m_typeInfo(typeInfo),
    m_superRTTI(superRTTI)
{
}

inline std::size_t RTTI::GetHashCode() const noexcept
{
    return m_typeInfo.hash_code();
}

inline const char* RTTI::GetName() const noexcept
{
    return m_typeInfo.name();
}

inline const RTTI* RTTI::GetSuperRTTI() const noexcept
{
    return m_superRTTI;
}

} /* namespace tgon */