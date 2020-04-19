#pragma once

#include "RTTI.h"

namespace tg
{

class RuntimeObject
{
/**@section Type */
public:
    using Super = void;
    using This = RuntimeObject;

/**@section Constructor */
public:
    RuntimeObject() noexcept = default;
    RuntimeObject(RuntimeObject&& rhs) noexcept = default;

/**@section Destructor */
public:
    virtual ~RuntimeObject() = default;
    
/**@section Operator */
public:
    RuntimeObject& operator=(RuntimeObject&& rhs) noexcept = default;

/**@section Method */
public:
    virtual const RTTI* GetRTTI() const = 0;
};

}

#define TGON_DECLARE_RTTI(classType)\
    using Super = This;\
    using This = classType;\
    \
    const tg::RTTI* GetRTTI() const override\
    {\
        static_assert(std::is_same_v<std::remove_const_t<std::remove_pointer_t<decltype(this)>>, This>, "TGON_DECLARE_RTTI didn't received the owner type as a parameter.");\
        return tg::GetRTTI<classType>();\
    }
