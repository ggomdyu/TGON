/**
 * @file    IModule.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include "Core/CoreObject.h"

namespace tgon
{

class TGON_API IModule :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(IModule)

/**@section Destructor */
public:
    virtual ~IModule() = 0;

/**@section Method */
public:
    /**@brief   Updates the module. */
    virtual void Update() = 0;
};

inline IModule::~IModule() = default;

} /* namespace tgon */
