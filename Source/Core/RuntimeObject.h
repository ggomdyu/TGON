/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "RTTI.h"

namespace tgon
{

class RuntimeObject
{
/**@section Type */
public:
    using Super = void;
    using This = RuntimeObject;

/**@section Constructor */
public:
    RuntimeObject() {}
    RuntimeObject(RuntimeObject&& rhs) noexcept = default;

/**@section Destructor */
public:
    virtual ~RuntimeObject() {}
    
/**@section Operator */
public:
    RuntimeObject& operator=(RuntimeObject&& rhs) noexcept = default;

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
        static_assert(std::is_same_v<std::remove_const_t<std::remove_pointer_t<decltype(this)>>, This>, "TGON_DECLARE_RTTI didn't received the owner type as a parameter.");\
        return tgon::GetRTTI<classType>();\
    }
