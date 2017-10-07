/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 * @brief       Define class which becomes the base of all objects.
 */

#pragma once
#include <memory>
#include <typeinfo>

#include "Core/Platform/Config.h"

namespace tgon
{
namespace object
{

struct TGON_API TypeInfo final
{
/* @section Ctor/Dtor */
public:
    TypeInfo(const std::type_info& rawTypeInfo, const TypeInfo* superTypeInfo) noexcept;

/* @section Public method */
public:
    std::size_t GetHashCode() const noexcept;
    const char* GetName() const noexcept;

    const TypeInfo* GetSuperTypeInfo() const noexcept;

/* @section Private variable */
private:
    const std::type_info& m_rawTypeInfo;
    const TypeInfo* m_superTypeInfo;
};

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

    /* @brief   Get static bound type information. */
    template <typename _Type>
    friend const TypeInfo* GetTypeInfo();
    
    /* @brief   Get dynamic bound type information. */
    virtual const TypeInfo* GetTypeInfo() const noexcept = 0;
};

template <typename _Type>
const TypeInfo* GetTypeInfo()
{
    static const TypeInfo typeInfo(typeid(_Type), GetTypeInfo<typename _Type::SuperType>());
    return &typeInfo;
}

template <>
inline const TypeInfo* GetTypeInfo<void>()
{
    return nullptr;
}

} /* namespace object */
} /* namespace tgon */

#define TGON_OBJECT(classType)\
    using SuperType = ThisType;\
    using ThisType = classType;\
    \
    virtual const tgon::object::TypeInfo* GetTypeInfo() const noexcept override\
    {\
        return tgon::object::GetTypeInfo<classType>();\
    }
