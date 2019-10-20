/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Platform/Config.h"
#include "Core/NonCopyable.h"

#include "RTTI.h"

namespace tgon
{

class TGON_API RuntimeObject :
    private NonCopyable
{
/**@section Type */
public:
    using SuperType = void;
    using ThisType = RuntimeObject;

/**@section Destructor */
public:
    virtual ~RuntimeObject() {}

/**@section Method */
public:
    virtual const RTTI* GetRTTI() const = 0;
};

} /* namespace tgon */

#define TGON_DECLARE_RTTI(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
