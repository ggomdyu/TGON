/**
 * @file    RTTIUtility.h
 * @author  ggomdyu
 * @since   08/17/2017
 */

#pragma once
#include <type_traits>

namespace tgon
{

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
        if (rtti == GetRTTI<_CastToType>())
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

template <typename _Type>
inline typename std::enable_if<IsPureType<_Type>, const RTTI*>::type GetRTTI()
{
    using PureType = PurifyType<_Type>;
    
    static const RTTI rtti(typeid(PureType), GetRTTI<typename PureType::SuperType>());
    return &rtti;
}
    
template <typename _Type>
inline typename std::enable_if<!IsPureType<_Type>, const RTTI*>::type GetRTTI()
{
    return GetRTTI<PurifyType<_Type>>();
}

template <>
inline const RTTI* GetRTTI<void>()
{
    return nullptr;
}

} /* namespace tgon */
