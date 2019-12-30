/**
 * @file    Module.h
 * @author  ggomdyu
 * @since   07/13/2016
 */

#pragma once
#include "Core/Object.h"

namespace tgon
{

class Module :
    public Object
{
public:
    TGON_DECLARE_RTTI(Module)

/* @section Destructor */
public:
    virtual ~Module() = default;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update() {}
};

} /* namespace tgon */
