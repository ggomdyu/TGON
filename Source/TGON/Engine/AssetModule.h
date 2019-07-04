/**
 * @file    ResourceModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <memory>
#include <map>

#include "Core/IAsset.h"
#include "Core/DelegateChain.h"
#include "String/StringHash.h"

#include "IModule.h"

namespace tgon
{

class TGON_API AssetModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(AssetModule);

/* @section Constructor */
public:
    AssetModule();

/* @section Destructor */
public:
    virtual ~AssetModule() override = default;

/* @section Method */
public:
    virtual void Update() override;

    void PurgeResource(const StringViewHash& resourceName);
    
private:
//    void RepairReleasedAsset();
    
/* @section Event handler */
public:
//    DelegateChain<void()> OnAppEnterBackground;
    
/* @section Variable */
private:
};

} /* namespace tgon */
