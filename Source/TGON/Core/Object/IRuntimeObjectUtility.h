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