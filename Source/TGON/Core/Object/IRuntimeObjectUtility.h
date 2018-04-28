/**
 * @filename    IRuntimeObjectUtility.h
 * @author      ggomdyu
 * @since       08/17/2017
 */

#pragma once
#include <cassert>
#include <type_traits>

namespace tgon
{

template <typename _CastToType, typename _CastFromType, std::enable_if<std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, std::enable_if_t<!std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<std::remove_pointer_t<_CastToType>::type>())
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