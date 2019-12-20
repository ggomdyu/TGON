#include "PrecompiledHeader.h"

#include "AssetModule.h"

namespace tgon
{

std::shared_ptr<Texture> AssetModule::GetTexture(const StringViewHash& path)
{
    m_mutex.lock();
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<Texture>(path.Data(), FilterMode::Bilinear, WrapMode::Clamp, false, false)}).first;
    }
    
    m_mutex.unlock();
    
    return std::any_cast<std::shared_ptr<Texture>>(iter->second);
}

std::shared_ptr<const Texture> AssetModule::GetTexture(const StringViewHash& path) const
{
    return const_cast<AssetModule*>(this)->GetTexture(path);
}

std::shared_ptr<AudioBuffer> AssetModule::GetAudioBuffer(const StringViewHash& path)
{
    m_mutex.lock();
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.insert({path, std::make_shared<AudioBuffer>(path.Data())}).first;
    }
    
    m_mutex.unlock();
    
    return std::any_cast<std::shared_ptr<AudioBuffer>>(iter->second);
}

std::shared_ptr<const AudioBuffer> AssetModule::GetAudioBuffer(const StringViewHash& path) const
{
    return const_cast<AssetModule*>(this)->GetAudioBuffer(path);
}

std::shared_ptr<FontAtlas> AssetModule::GetFontAtlas(const StringViewHash& path)
{
    m_mutex.lock();
    
    auto iter = m_resourceCache.find(path);
    if (iter == m_resourceCache.end())
    {
        iter = m_resourceCache.emplace(path, std::make_shared<FontAtlas>(std::make_shared<Font>(path.Data(), m_fontFactory.GetFTLibrary()))).first;
    }
    
    m_mutex.unlock();
    
    return std::any_cast<std::shared_ptr<FontAtlas>>(iter->second);
}

std::shared_ptr<const FontAtlas> AssetModule::GetFontAtlas(const StringViewHash& path) const
{
    return const_cast<AssetModule*>(this)->GetFontAtlas(path);
}

void AssetModule::PurgeResource(const StringViewHash& path)
{
    m_resourceCache.erase(path);
}

} /* namespace tgon */
