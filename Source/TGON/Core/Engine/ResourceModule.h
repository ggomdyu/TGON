/**
 * @file    ResourceModule.h
 * @author  ggomdyu
 * @since   08/07/2018
 */

#pragma once
#include "IModule.h"

namespace tgon
{

class TGON_API ResourceModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(ResourceModule);

/* @section Public constructor */
public:
    ResourceModule();

/* @section Public destructor */
public:
    virtual ~ResourceModule() override = default;

/* @section Public method */
public:
    /* @brief                   Updates the ResourceModule. */
    virtual void Update() override;
    
/* @section Private variable */
private:
    uint64_t m_lastRecordedTickTime;
    float m_timeScale;
    float m_tickTime;
};

} /* namespace tgon */
