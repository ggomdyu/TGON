/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include "RTTI.h"

namespace tgon
{

class TGON_API RuntimeObject
{
/* @section Public type */
public:
    using SuperType = void;
    using ThisType = RuntimeObject;

/* @section Public destructor */
public:
    virtual ~RuntimeObject() = 0;

/* @section Public method */
public:
    /* @brief   Gets dynamic bound type information. */
    virtual const RTTI* GetRTTI() const = 0;

    /* @brief   Get static bound type information. */
    template <typename _Type>
    friend const RTTI* GetRTTI() noexcept;
};

inline RuntimeObject::~RuntimeObject() = default;

template <typename _Type>
inline const RTTI* GetRTTI() noexcept
{
    using ClassType = std::remove_pointer_t<std::decay_t<_Type>>;
    
    static_assert(std::is_base_of<RuntimeObject, ClassType>::value, "GetRTTI only accepts template parameter that inherited from IRuntimeObject.");
    
    static const RTTI rtti(typeid(ClassType), GetRTTI<typename ClassType::SuperType>());
    return &rtti;
}

template <>
inline const RTTI* GetRTTI<void>() noexcept
{
    return nullptr;
}

} /* namespace tgon */

#define TGON_RUNTIME_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::RTTI* GetRTTI() const override\
    {\
        return tgon::GetRTTI<classType>();\
    }
