/**
 * @file    ResourceModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include <memory>
#include <map>

#include "Core/Object/IResource.h"

#include "IModule.h"

namespace tgon
{

class TGON_API ResourceModule final :
	public IModule
{
public:
    TGON_DECLARE_RTTI(ResourceModule);

/* @section Constructor */
public:
    ResourceModule();

/* @section Destructor */
public:
    virtual ~ResourceModule() override = default;

/* @section Method */
public:
    virtual void Update() override;

    void PurgeResource(const char* resourceName);
    
/* @section Variable */
private:
    std::map<size_t, std::shared_ptr<IResource>> m_resourcePool;
};

} /* namespace tgon */
