/**
 * @file    AssetModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <mutex>
#include <any>

#include "Text/StringHash.h"
#include "Audio/AudioBuffer.h"
#include "Graphics/Texture.h"
#include "Drawing/FontFactory.h"

#include "Module.h"

namespace tgon
{

class AssetModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(AssetModule);

/* @section Method */
public:
    std::shared_ptr<Texture> GetTexture(const StringViewHash& path);
    std::shared_ptr<AudioBuffer> GetAudioBuffer(const StringViewHash& path);
    std::shared_ptr<Font> GetFont(const StringViewHash& path);
    
    void PurgeResource(const StringViewHash& path);
    
/* @section Variable */
private:
    FontFactory m_fontFactory;
    std::unordered_map<StringHash, std::any> m_resourceCache;
    std::mutex m_mutex;
};

} /* namespace tgon */
