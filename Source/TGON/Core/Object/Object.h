/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <cstdint>
#include <cstddef>

#include "TypeInfo.h"

#include "Core/Platform/Config.h"

namespace tgon
{
namespace object
{

class TGON_API Object
{
/* @section Public type */
public:
    using SuperType = void;
    using ThisType = Object;

/* @section Ctor/Dtor */
public:
    virtual ~Object() = default;

/* @section Public method */
public:
    /* @brief   Copy this object. */
    virtual std::shared_ptr<Object> Clone() const;

    /* @brief   Get dynamic bound type information. */
    virtual const TypeInfo& GetDynamicTypeInfo() const noexcept = 0;

    /* @brief   Get static bound type information. */
    static const TypeInfo& GetStaticTypeInfo() noexcept;
};

inline std::shared_ptr<Object> Object::Clone() const
{
    return nullptr;
}

inline const TypeInfo& Object::GetStaticTypeInfo() noexcept
{
    static const TypeInfo typeInfo("tgon::object::Object", nullptr);
    return typeInfo;
}

} /* namespace object */
} /* namespace tgon */

#define TGON_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::object::TypeInfo& GetDynamicTypeInfo() const noexcept override\
    {\
        return classType::GetStaticTypeInfo();\
    }\
    static const tgon::object::TypeInfo& GetStaticTypeInfo() noexcept\
    {\
        static const tgon::object::TypeInfo typeInfo(#classType, &SuperType::GetStaticTypeInfo());\
        return typeInfo;\
    }
