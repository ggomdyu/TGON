#pragma once

#include <typeinfo>

#include "TypeTraits.h"

namespace tg
{

class RTTI final
{
/* @section Constructor */
public:
    RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept;

/* @section Method */
public:
    size_t GetHashCode() const noexcept;
    const char* GetName() const noexcept;
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
inline typename std::enable_if_t<IsPure<_Type>, const RTTI*> GetRTTI()
{
    using PureType = Pure<_Type>;

    static const RTTI rtti(typeid(PureType), GetRTTI<typename PureType::Super>());
    return &rtti;
}

template <typename _Type>
inline typename std::enable_if_t<!IsPure<_Type>, const RTTI*> GetRTTI()
{
    return GetRTTI<Pure<_Type>>();
}

template <>
inline const RTTI* GetRTTI<void>()
{
    return nullptr;
}

inline RTTI::RTTI(const std::type_info& typeInfo, const RTTI* superRTTI) noexcept :
    m_typeInfo(&typeInfo),
    m_superRTTI(superRTTI)
{
}

inline size_t RTTI::GetHashCode() const noexcept
{
    return m_typeInfo->hash_code();
}

inline const char* RTTI::GetName() const noexcept
{
    return m_typeInfo->name();
}

inline const RTTI* RTTI::GetSuperRTTI() const noexcept
{
    return m_superRTTI;
}

inline bool RTTI::operator==(const RTTI& rhs) const noexcept
{
    return m_typeInfo == rhs.m_typeInfo;
}

inline bool RTTI::operator!=(const RTTI& rhs) const noexcept
{
    return !(*this == rhs);
}

inline bool RTTI::operator<(const RTTI& rhs) const noexcept
{
    return m_typeInfo->before(*rhs.m_typeInfo);
}

inline bool RTTI::operator>=(const RTTI& rhs) const noexcept
{
    return !(*this < rhs);
}

inline bool RTTI::operator>(const RTTI& rhs) const noexcept
{
    return (rhs < *this);
}

inline bool RTTI::operator<=(const RTTI& rhs) const noexcept
{
    return !(*this > rhs);
}

}

namespace std
{

template <>
struct hash<tg::RTTI>
{
/* @section Method */
public:
    size_t operator()(const tg::RTTI& rhs) const noexcept;
};

inline size_t hash<tg::RTTI>::operator()(const tg::RTTI& rhs) const noexcept
{
    return rhs.GetHashCode();
}
    
}
