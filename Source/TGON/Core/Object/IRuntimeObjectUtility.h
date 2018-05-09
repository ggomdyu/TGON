/**
 * @filename    IRuntimeObjectUtility.h
 * @author      ggomdyu
 * @since       08/17/2017
 */

#pragma once
#include <cassert>
#include <type_traits>

#include "IRuntimeObject.h"

namespace tgon
{

/* @brief   Get static bound type information. */
template <typename _Type>
inline const RTTI* GetRTTI()
{
    using ClassType = std::remove_pointer_t<std::decay_t<_Type>>;

    static_assert(std::is_convertible<ClassType*, IRuntimeObject*>::value, "GetRTTI only accepts template parameter that inherited from IRuntimeObject.");

    static const RTTI rtti(typeid(ClassType), GetRTTI<typename ClassType::SuperType>());
    return &rtti;
}

/* @brief   Get static bound type information. */
template <>
inline const RTTI* GetRTTI<void>()
{
    return nullptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if<std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if<!std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<std::remove_pointer_t<_CastToType>>())
        {
            return reinterpret_cast<_CastToType>(ptr);
        }
        else
        {
            rtti = rtti->GetSuperRTTI();
        }
    }

    return nullptr;
}

} /* namespace tgon */