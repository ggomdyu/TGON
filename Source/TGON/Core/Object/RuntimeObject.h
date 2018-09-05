/**
 * @file    RuntimeObject.h
 * @author  ggomdyu
 * @since   10/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Object/TypeTraits.h"

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
};

inline RuntimeObject::~RuntimeObject() = default;

template <typename _Type>
inline auto GetRTTI() -> typename std::enable_if<IsPureType<_Type>, const RTTI*>::type
{
    using PureType = PurifyType<_Type>;
    
    static_assert(std::is_base_of<RuntimeObject, PureType>::value, "GetRTTI only accepts template parameter that inherited from RuntimeObject.");

    static const RTTI rtti(typeid(PureType), GetRTTI<typename PureType::SuperType>());
    return &rtti;
}
    
template <typename _Type>
inline auto GetRTTI() -> typename std::enable_if<!IsPureType<_Type>, const RTTI*>::type
{
    return GetRTTI<PurifyType<_Type>>();
}

template <>
inline const RTTI* GetRTTI<void>()
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
