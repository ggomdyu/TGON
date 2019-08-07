/**
 * @file    RTTI.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include <typeinfo>
#include <cstdint>

#include "TypeTraits.h"

namespace tgon
{

struct RTTI final
{
/* @section Constructor */
public:
    RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept;

/* @section Method */
public:
    /**@brief   Returns the type hash code. */
    size_t GetHashCode() const noexcept;
    
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

template <typename _Type>
inline typename std::enable_if<IsPureValue<_Type>, const RTTI*>::type GetRTTI()
{
    using PureType = Pure_t<_Type>;
    
    static const RTTI rtti(typeid(PureType), GetRTTI<typename PureType::SuperType>());
    return &rtti;
}

template <typename _Type>
inline typename std::enable_if<!IsPureValue<_Type>, const RTTI*>::type GetRTTI()
{
    return GetRTTI<Pure_t<_Type>>();
}

template <>
inline const RTTI* GetRTTI<void>()
{
    return nullptr;
}

} /* namespace tgon */

namespace std
{

template<>
struct hash<tgon::RTTI>
{
/* @section Method */
public:
    size_t operator()(const tgon::RTTI& rhs) const noexcept;
};

inline size_t hash<tgon::RTTI>::operator()(const tgon::RTTI& rhs) const noexcept
{
    return rhs.GetHashCode();
}
    
} /* namespace std */
