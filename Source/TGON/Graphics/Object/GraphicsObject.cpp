#include "PrecompiledHeader.h"

#include "GraphicsObject.h"

namespace tgon
{
    
void GraphicsObject::Update()
{
    m_transform.Update();
}

Transform& GraphicsObject::GetTransform() noexcept
{
    return m_transform;
}

const Transform& GraphicsObject::GetTransform() const noexcept
{
    return m_transform;
}
    
} /* namespace tgon */
