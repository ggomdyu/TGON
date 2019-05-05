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
/* @section Constructor */
public:
    RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept;

/* @section Method */
public:
    /**@brief   Returns unique hash code for each type. */
    std::size_t GetHashCode() const noexcept;
    
    /**@brief   Returns the type name of RTTI owner. */
    const char* GetName() const noexcept;

    /**@brief   Returns the parent type's RTTI. */
    const RTTI* GetSuperRTTI() const noexcept;

/* @section Operator */
public:
    bool operator==(const RTTI& rhs) const noexcept;
    bool operator!=(const RTTI& rhs) const noexcept;
    bool operator<(const RTTI& rhs) const noexcept;
    bool operator>=(const RTTI& rhs) const noexcept;
    bool operator>(const RTTI& rhs) const noexcept;
    bool operator<=(const RTTI& rhs) const noexcept;

/* @section Variable */
private:
    const std::type_info* m_typeInfo;

    const RTTI* m_superRTTI;
};

} /* namespace tgon */

namespace std
{

template<>
struct hash<tgon::RTTI>
{
/* @section Type */
public:
    using argument_type = tgon::RTTI;
    using result_type = size_t;

/* @section Method */
public:
    size_t operator()(const tgon::RTTI& rhs) const noexcept;
};

inline size_t hash<tgon::RTTI>::operator()(const tgon::RTTI& rhs) const noexcept
{
    return rhs.GetHashCode();
}

} /* namespace std */