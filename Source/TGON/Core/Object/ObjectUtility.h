/**
 * @filename    ObjectUtility.h
 * @author      ggomdyu
 * @since       08/17/2017
 */

#pragma once
#include <cstdint>
#include <type_traits>

#include "Object.h"

namespace tgon
{
namespace object
{

template <typename _CastToType>
inline _CastToType* DynamicCast(Object* object)
{
    using CastToType = typename std::remove_reference<typename std::remove_pointer<_CastToType>::type>::type;

    static_assert(std::is_convertible<CastToType*, Object*>::value, "The given cast type is not base of Object!");

    const TypeInfo* typeInfo = &object->GetDynamicType();
    while (typeInfo != nullptr)
    {
        if (typeInfo == &CastToType::GetStaticType())
        {
            return reinterpret_cast<CastToType*>(object);
        }

        typeInfo = &typeInfo->GetSuperType();
    }
    
    return nullptr;
}

} /* namespace object */
} /* namespace tgon */
