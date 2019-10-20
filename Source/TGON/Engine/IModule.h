/**
 * @file    IModule.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include "Core/Object.h"

namespace tgon
{

class TGON_API IModule :
    public Object
{
public:
    TGON_DECLARE_RTTI(IModule)

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update() {}
};

} /* namespace tgon */
