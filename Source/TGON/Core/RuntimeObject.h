/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Core/NonCopyable.h"

#include "RTTI.h"

namespace tgon
{

class RuntimeObject :
    private NonCopyable
{
/**@section Type */
public:
    using Super = void;
    using This = RuntimeObject;

/**@section Destructor */
public:
    virtual ~RuntimeObject() {}

/**@section Method */
public:
    virtual const RTTI* GetRTTI() const = 0;
};

} /* namespace tgon */

#define TGON_DECLARE_RTTI(classType)\
    using Super = This;\
    using This = classType;\
    \
    const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
