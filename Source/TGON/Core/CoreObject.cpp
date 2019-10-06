#include "PrecompiledHeader.h"

#include "CoreObject.h"

namespace tgon
{

CoreObject::CoreObject(const StringHash& name) :
    m_name(name)
{
}

CoreObject::CoreObject(StringHash&& name) :
    m_name(std::move(name))
{
}

void CoreObject::SetName(const StringHash& name)
{
    m_name = name;
}

const StringHash& CoreObject::GetName() const noexcept
{
    return m_name;
}

} /* namespace tgon */