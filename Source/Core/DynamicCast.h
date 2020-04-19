#pragma once

#include <type_traits>

#include "RTTI.h"

namespace tg
{

template <typename _CastToType, typename _CastFromType, typename std::enable_if_t<std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast(_CastFromType&& ptr) noexcept
{
    return ptr;
}

template <typename _CastToType, typename _CastFromType, typename std::enable_if_t<!std::is_convertible_v<_CastFromType, _CastToType>>* = nullptr>
inline _CastToType DynamicCast(_CastFromType&& ptr) noexcept
{
    const RTTI* rtti = ptr->GetRTTI();
    while (rtti != nullptr)
    {
        if (rtti == GetRTTI<_CastToType>())
        {
            return reinterpret_cast<_CastToType>(std::forward<_CastFromType>(ptr));
        }
        else
        {
            rtti = rtti->GetSuperRTTI();
        }
    }
    
    return nullptr;
}

}
