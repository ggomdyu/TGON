/**
 * @file    Module.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include "Core/RuntimeObject.h"

namespace tgon
{

class Module :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Module)

/* @section Destructor */
public:
    virtual ~Module() = default;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Destroy() {}
    virtual void Update() {}
};

} /* namespace tgon */
