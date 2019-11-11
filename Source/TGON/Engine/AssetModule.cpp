#include "PrecompiledHeader.h"

#include "AssetModule.h"

namespace tgon
{

std::shared_ptr<Texture> AssetModule::GetTexture(const StringViewHash& path)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<Texture>(path.Data(), FilterMode::Bilinear, WrapMode::Clamp, false, false)}).first;
    }
    
    return std::any_cast<std::shared_ptr<Texture>>(iter->second);
}

std::shared_ptr<AudioBuffer> AssetModule::GetAudioBuffer(const StringViewHash& path)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<AudioBuffer>(path)}).first;
    }
    
    return std::any_cast<std::shared_ptr<AudioBuffer>>(iter->second);
}

std::shared_ptr<Font> AssetModule::GetFont(const StringViewHash& path)
{
    std::lock_guard<std::mutex> lockGuard(m_mutex);
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<Font>(path.Data(), m_fontFactory.GetFTLibrary())}).first;
    }
    
    return std::any_cast<std::shared_ptr<Font>>(iter->second);
}

void AssetModule::PurgeResource(const StringViewHash& path)
{
    m_resourceCache.erase(path);
}

} /* namespace tgon */
