/**
 * @file    AssetModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <any>

#include "String/StringHash.h"

#include "IModule.h"

namespace tgon
{

class TGON_API Asset
{
private:
    StringHash m_path;
    std::any m_resource;
};


class TGON_API AssetModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(AssetModule);

/* @section Destructor */
public:
    virtual ~AssetModule() override = default;

/* @section Method */
public:
    virtual void Update() override;
    std::shared_ptr<Asset> Load(const StringViewHash& path);
    void Store(std::shared_ptr<Asset> asset);
    void PurgeResource(const StringViewHash& resourceName);
    
/* @section Variable */
private:
    std::unordered_map<size_t, std::shared_ptr<Asset>> m_resourceCache;
};

} /* namespace tgon */
