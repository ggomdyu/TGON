/**
 * @filename    ObjectUtility.h
 * @author      ggomdyu
 * @since       08/17/2017
 */

#pragma once
#include <cstdint>
#include <type_traits>
#include <cassert>

#include "Object.h"

namespace tgon
{
namespace object
{
namespace detail
{

template <typename _CastToType, typename _CastFromType, bool _IsStaticCastable = std::is_convertible<_CastFromType, _CastToType>::value>
struct DynamicCastHelper;

template <typename _CastToType, typename _CastFromType>
struct DynamicCastHelper<_CastToType, _CastFromType, false>
{
    static _CastToType DynamicCast(_CastFromType object);
};

template <typename _CastToType, typename _CastFromType>
inline _CastToType DynamicCastHelper<_CastToType, _CastFromType, false>::DynamicCast(_CastFromType object)
{
    static_assert(std::is_convertible<_CastToType, Object*>::value, "DynamicCast _CastToType is not base of Object.");
    static_assert(std::is_convertible<_CastFromType, Object*>::value, "DynamicCast _CastFromType is not base of Object.");

    assert(object != nullptr && "DynamicCast cast target can't be nullptr.");

    const TypeInfo* typeInfo = &object->GetDynamicTypeInfo();
    while (typeInfo != nullptr)
    {
        using CastToType = typename std::remove_pointer<_CastToType>::type;
        if (typeInfo == &CastToType::GetStaticTypeInfo())
        {
            return reinterpret_cast<_CastToType>(object);
        }

        typeInfo = &typeInfo->GetSuperTypeInfo();
    }
    
    return nullptr;
}

template <typename _CastToType, typename _CastFromType>
struct DynamicCastHelper<_CastToType, _CastFromType, true>
{
public:
    static _CastToType DynamicCast(_CastFromType object) noexcept;
};

template <typename _CastToType, typename _CastFromType>
inline _CastToType DynamicCastHelper<_CastToType, _CastFromType, true>::DynamicCast(_CastFromType object) noexcept
{
    return object;
}

} /* namespace detail */

template <typename _CastToType, typename _CastFromType>
inline _CastToType DynamicCast(_CastFromType object)
{
    return detail::DynamicCastHelper<_CastToType, _CastFromType>::DynamicCast(object);
}

} /* namespace object */
} /* namespace tgon */
