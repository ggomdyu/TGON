/**
 * @file    AssetModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <any>

#include "Text/StringHash.h"
#include "Audio/AudioBuffer.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureAtlas.h"

#include "IModule.h"

namespace tgon
{

class TGON_API AssetModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(AssetModule);

/* @section Method */
public:
    std::shared_ptr<Texture> LoadTexture(const StringViewHash& path);
    std::shared_ptr<AudioBuffer> LoadAudioBuffer(const StringViewHash& path);
    void PurgeResource(const StringViewHash& path);
    
/* @section Variable */
private:
    std::unordered_map<StringHash, std::any> m_resourceCache;
};

} /* namespace tgon */
