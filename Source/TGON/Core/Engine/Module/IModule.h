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
    TGON_DECLARE_RTTI(IModule);

/**@section Method */
public:
    /**@brief   Updates the module. */
    virtual void Update() = 0;
};

} /* namespace tgon */
