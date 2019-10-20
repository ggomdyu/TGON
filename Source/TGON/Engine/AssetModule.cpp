#include "PrecompiledHeader.h"

#include "AssetModule.h"

namespace tgon
{

std::shared_ptr<Texture> AssetModule::LoadTexture(const StringViewHash& path)
{
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<Texture>(path, FilterMode::Bilinear, WrapMode::Clamp, false, false)}).first;
    }
    
    return std::any_cast<std::shared_ptr<Texture>>(iter->second);
}

std::shared_ptr<AudioBuffer> AssetModule::LoadAudioBuffer(const StringViewHash& path)
{
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<AudioBuffer>(path)}).first;
    }
    
    return std::any_cast<std::shared_ptr<AudioBuffer>>(iter->second);
}

void AssetModule::PurgeResource(const StringViewHash& path)
{
    m_resourceCache.erase(path);
}

} /* namespace tgon */
