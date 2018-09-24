/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include "RTTI.h"
#include "RTTIUtility.h"
#include "TypeTraits.h"

namespace tgon
{

class TGON_API RuntimeObject
{
/**@section Public type */
public:
    using SuperType = void;
    using ThisType = RuntimeObject;

/**@section Public destructor */
public:
    virtual ~RuntimeObject() = 0;

/**@section Public method */
public:
    /**@brief   Gets dynamic bound type information. */
    virtual const RTTI* GetRTTI() const = 0;
};

inline RuntimeObject::~RuntimeObject() = default;

} /* namespace tgon */

#define TGON_RUNTIME_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
