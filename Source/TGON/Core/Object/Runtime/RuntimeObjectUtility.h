/**
 * @file    RuntimeObjectUtility.h
 * @author  ggomdyu
 * @since   08/17/2017
 */

#pragma once
#include <type_traits>
#include <cassert>

#include "RuntimeObject.h"

namespace tgon
{

/* @brief   Get static bound type information. */
template <typename _Type>
inline const RTTI* GetRTTI() noexcept
{
    using ClassType = std::remove_pointer_t<std::decay_t<_Type>>;
    
    static_assert(std::is_base_of<RuntimeObject, ClassType>::value, "GetRTTI only accepts template parameter that inherited from IRuntimeObject.");
    
    static const RTTI rtti(typeid(ClassType), GetRTTI<typename ClassType::SuperType>());
    return &rtti;
}

/* @brief   Get static bound type information. */
template <>
inline const RTTI* GetRTTI<void>() noexcept
{
    return nullptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if<std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr) noexcept
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if<!std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr) noexcept
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<std::remove_pointer_t<std::decay_t<_CastToType>>>())
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
