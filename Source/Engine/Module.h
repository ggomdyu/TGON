#pragma once

#include "Core/RuntimeObject.h"

namespace tg
{

class Module :
    public RuntimeObject
{
public:
    TGON_RTTI(Module)

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update() {}
};

}
