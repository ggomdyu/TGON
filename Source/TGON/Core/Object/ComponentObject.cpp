#include "PrecompiledHeader.pch"
#include "ComponentObject.h"

#include "IComponent.h"

namespace tgon
{
namespace object
{

void ComponentObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}

} /* namespace object */
} /* namespace tgon */

