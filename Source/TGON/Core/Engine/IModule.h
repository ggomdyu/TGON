/**
 * @file    IModule.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include "Core/Object/CoreObject.h"

namespace tgon
{

class TGON_API IModule :
    public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(IModule);

/* @section Public destructor */
public:
    virtual ~IModule() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
};
    
inline IModule::~IModule() = default;

} /* namespace tgon */
