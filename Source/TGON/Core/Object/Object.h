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
    virtual const TypeInfo& GetDynamicType() const noexcept = 0;

    /* @brief   Get static bound type information. */
    static const TypeInfo& GetStaticType() noexcept;
};

} /* namespace object */
} /* namespace tgon */

#define TGON_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::object::TypeInfo& GetDynamicType() const noexcept override\
    {\
        return classType::GetStaticType();\
    }\
    static const tgon::object::TypeInfo& GetStaticType() noexcept\
    {\
        static const tgon::object::TypeInfo typeInfo(#classType, &SuperType::GetStaticType());\
        return typeInfo;\
    }
