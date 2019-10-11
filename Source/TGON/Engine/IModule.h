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

/**@section Destructor */
public:
    virtual ~IModule() = 0;

/**@section Method */
public:
    virtual void Update() = 0;
};

inline IModule::~IModule() = default;

} /* namespace tgon */
