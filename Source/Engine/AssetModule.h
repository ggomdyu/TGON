/**
 * @file    AssetModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <mutex>
#include <any>
#include <unordered_map>

#include "Audio/AudioBuffer.h"
#include "Text/StringHash.h"
#include "Drawing/FontFactory.h"
#include "Graphics/Texture.h"
#include "Graphics/FontAtlas.h"

#include "Module.h"

namespace tgon
{

class AssetModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(AssetModule)

/* @section Type */
private:
    using ResourceCache = std::unordered_map<StringHash, std::any>;
    using ResourceUnitTable = std::vector<ResourceCache>;
    using ResourceUnit = size_t;

/**@section Constructor */
public:
    AssetModule();

/* @section Method */
public:
    template <typename _ResourceType>
    std::shared_ptr<_ResourceType> GetResource(const StringViewHash& path);
    template <typename _ResourceType>
    std::shared_ptr<const _ResourceType> GetResource(const StringViewHash& path) const;
    template <typename _ResourceType>
    void PurgeResource(const StringViewHash& path);
    template <typename _ResourceType>
    void PurgeResource();
    void PurgeAllResource();

private:
    template <typename _ResourceType>
    std::shared_ptr<_ResourceType> CreateResource(const StringViewHash& path) const;
    template <typename _ResourceType>
    ResourceUnit GetResourceUnit() const;

/* @section Variable */
private:
    std::mutex m_mutex;
    FontFactory m_fontFactory;
    mutable ResourceUnitTable m_resourceUnitTable;
    inline static ResourceUnit m_maxResourceUnit;
};

template<typename _ResourceType>
inline std::shared_ptr<_ResourceType> AssetModule::GetResource(const StringViewHash& path)
{
    std::lock_guard lock(m_mutex);

    ResourceCache resourceCache = m_resourceUnitTable[GetResourceUnit<_ResourceType>()];
    auto iter = resourceCache.find(path);
    if (iter == resourceCache.end())
    {
        iter = resourceCache.emplace(path, this->CreateResource<_ResourceType>(path)).first;
    }

    return std::any_cast<std::shared_ptr<_ResourceType>>(iter->second);
}

template<typename _ResourceType>
inline std::shared_ptr<const _ResourceType> AssetModule::GetResource(const StringViewHash& path) const
{
    return const_cast<AssetModule*>(this)->GetResource<_ResourceType>(path);
}

template <typename _ResourceType>
inline std::shared_ptr<_ResourceType> AssetModule::CreateResource(const StringViewHash& path) const
{
    return std::make_shared<_ResourceType>(path.Data());
}

template <>
inline std::shared_ptr<Texture> AssetModule::CreateResource(const StringViewHash& path) const
{
    auto image = Image::Create(path.Data());
    if (image.has_value() == false)
    {
        return nullptr;
    }

    return std::make_shared<Texture>(*image, FilterMode::Linear, WrapMode::Clamp, false, false);
}

template <>
inline std::shared_ptr<AudioBuffer> AssetModule::CreateResource(const StringViewHash& path) const
{
    auto audioBuffer = AudioBuffer::Create(path.Data());
    if (audioBuffer.has_value() == false)
    {
        return nullptr;
    }

    return std::make_shared<AudioBuffer>();
}

template <>
inline std::shared_ptr<Font> AssetModule::CreateResource(const StringViewHash& path) const
{
    return m_fontFactory.CreateFont(path.Data());
}

template <>
inline std::shared_ptr<FontAtlas> AssetModule::CreateResource(const StringViewHash& path) const
{
    ResourceCache resourceCache = m_resourceUnitTable[GetResourceUnit<Font>()];
    auto iter = resourceCache.find(path);
    if (iter == resourceCache.end())
    {
        iter = resourceCache.emplace(path, this->CreateResource<Font>(path)).first;
    }

    return std::make_shared<FontAtlas>(std::any_cast<std::shared_ptr<Font>>(iter->second));
}

template<typename _ResourceType>
inline AssetModule::ResourceUnit AssetModule::GetResourceUnit() const
{
    static ResourceUnit resourceUnit = [&]()
    {
        ResourceUnit ret = m_maxResourceUnit;
        m_resourceUnitTable.resize(++m_maxResourceUnit);
        return ret;
    } ();

    return resourceUnit;
}

template<typename _ResourceType>
inline void AssetModule::PurgeResource(const StringViewHash& path)
{
    m_resourceUnitTable[GetResourceUnit<Font>()].erase(path);
}

template <typename _ResourceType>
inline void AssetModule::PurgeResource()
{
    m_resourceUnitTable[GetResourceUnit<Font>()].clear();
}

inline void AssetModule::PurgeAllResource()
{
    m_resourceUnitTable.clear();
}

} /* namespace tgon */
