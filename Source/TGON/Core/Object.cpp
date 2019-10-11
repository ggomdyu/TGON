#include "PrecompiledHeader.h"

#include "Object.h"

namespace tgon
{

Object::Object(const StringHash& name) :
    m_name(name)
{
}

Object::Object(StringHash&& name) :
    m_name(std::move(name))
{
}

void Object::SetName(const StringHash& name)
{
    m_name = name;
}

const StringHash& Object::GetName() const noexcept
{
    return m_name;
}

} /* namespace tgon */
