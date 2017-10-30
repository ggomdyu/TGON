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
namespace object
{

template <typename _CastToType, typename _CastFromType, typename std::enable_if< std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if< !std::is_convertible<_CastFromType, _CastToType>::value>::type* = nullptr>
inline _CastToType DynamicCast(_CastFromType ptr)
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<typename std::remove_pointer<_CastToType>::type>())
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

} /* namespace object */
} /* namespace tgon */
