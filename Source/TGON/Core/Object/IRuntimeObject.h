/**
 * @file    IRuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "RTTI.h"

namespace tgon
{

class IRuntimeObject
{
/* @section Public type */
public:
    using SuperType = void;
    using ThisType = IRuntimeObject;

/* @section Public destructor */
public:
    virtual ~IRuntimeObject() = default;

/* @section Public method */
public:
    /* @brief   Gets dynamic bound type information. */
    virtual const RTTI* GetRTTI() const = 0;
};

} /* namespace tgon */

#define TGON_RUNTIME_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
