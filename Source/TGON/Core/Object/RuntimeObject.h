/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include "RTTI.h"
#include "RTTIUtility.h"

namespace tgon
{

class TGON_API RuntimeObject
{
/**@section Type */
public:
    using SuperType = void;
    using ThisType = RuntimeObject;

/**@section Destructor */
public:
    virtual ~RuntimeObject() = 0;

/**@section Method */
public:
    /**@brief   Gets a runtime type information of this instance. */
    virtual const RTTI* GetRTTI() const = 0;
};

inline RuntimeObject::~RuntimeObject() = default;

} /* namespace tgon */

#define TGON_DECLARE_RTTI(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
