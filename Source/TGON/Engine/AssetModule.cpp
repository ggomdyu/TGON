#include "PrecompiledHeader.h"

#include "AssetModule.h"

namespace tgon
{

void AssetModule::Update()
{
}

void AssetModule::PurgeResource(const StringViewHash& resourceName)
{
    m_resourceCache.erase(resourceName.GetHashCode());
}

} /* namespace tgon */
