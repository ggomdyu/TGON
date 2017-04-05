#include "PrecompiledHeader.h"
#include "IGraphicsInstance.h"

namespace tgon
{

IGraphicsInstance::IGraphicsInstance()
{
}


IGraphicsInstance::~IGraphicsInstance()
{
}

EGraphicsInstanceState IGraphicsInstance::GetInstanceState() const noexcept
{
    return m_state;
}

} /* namespace tgon */