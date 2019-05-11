#include "PrecompiledHeader.h"

#include "IResource.h"


namespace tgon
{

IResource::IResource(size_t id) :
    m_id(id)
{
}

const size_t IResource::GetID() const noexcept
{
    return m_id;
}

} /* namespace tgon */