/**
 * @file    RTTI.h
 * @author  ggomdyu
 * @since   10/29/2017
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
    RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept :
        m_typeInfo(typeInfo),
        m_superRTTI(superRTTI)
    {
    }

/* @section Public method */
public:
    /* @brief   Returns unique hash code for each type. */
    std::size_t GetHashCode() const noexcept
    {
        return m_typeInfo.hash_code();
    }
    
    /* @brief   Returns the type name of RTTI owner. */
    const char* GetName() const noexcept
    {
        return m_typeInfo.name();
    }

    /* @brief   Returns the parent type's RTTI. */
    const RTTI* GetSuperRTTI() const noexcept
    {
        return m_superRTTI;
    }
    
/* @section Private variable */
private:
    const std::type_info& m_typeInfo;
    const RTTI* m_superRTTI;
};

} /* namespace tgon */
