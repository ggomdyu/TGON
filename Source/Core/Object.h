/**
 * @file    Object.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include "RuntimeObject.h"

#include "Text/StringHash.h"

namespace tgon
{

class Object :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Object)
    
/**@section Constructor */
public:
    Object() = default;
    Object(const StringHash& name);
    Object(StringHash&& name) noexcept;
    Object(Object&& rhs) noexcept;

/**@section Operator */
public:
    Object& operator=(Object&& rhs) noexcept;

/**@section Method */
public:
    void SetName(const StringHash& name);
    void SetName(StringHash&& name);
    const StringHash& GetName() const noexcept;

/**@section Variable */
private:
    StringHash m_name;
};

inline Object::Object(const StringHash& name) :
    m_name(name)
{
}

inline Object::Object(StringHash&& name) noexcept :
    m_name(std::move(name))
{
}

inline Object::Object(Object&& rhs) noexcept :
    m_name(std::move(rhs.m_name))
{
}

inline Object& Object::operator=(Object&& rhs) noexcept
{
    m_name = std::move(rhs.m_name);
    return *this;
}

inline void Object::SetName(const StringHash& name)
{
    m_name = name;
}

inline void Object::SetName(StringHash&& name)
{
    m_name = std::move(name);
}

inline const StringHash& Object::GetName() const noexcept
{
    return m_name;
}

} /* namespace tgon */
