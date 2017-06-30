/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include "Core/Platform/Config.h"
#include "Core/Utility/Array.h"

#include "TypeInfo.h"

namespace tgon
{
namespace object
{

class TGON_API Object
{
/**
 * @section Type definition
 */
public:
	using Super = void;
	using This = Object;

/**
 * @section Ctor/Dtor
 */
public:
    Object() = default;
	virtual ~Object() = default;

/**
 * @section Public method
 */
public:
	virtual std::size_t GetHashCode() const = 0;

    virtual const char* GetTypeName() const noexcept = 0;
};

} /* namespace object */
} /* namespace tgon */

#define TGON_MAKE_OBJECT_INTERFACE(classType)\
    using Super = This;\
	using This = classType;\
	\
    virtual std::size_t GetHashCode() const noexcept override\
    {\
        return Foo::GetTypeInfo().GetHashCode();\
    }\
    virtual const char* GetTypeName() const noexcept override\
    {\
        return Foo::GetTypeInfo().GetTypeName().CStr();\
    }\
    static const tgon::object::TypeInfo<GetArraySize(#classType)>& GetTypeInfo() noexcept\
    {\
        tgon::object::TypeInfo<GetArraySize(#classType)> typeInfo(#classType);\
        return typeInfo;\
    }

// Todo: Implement interface's below
//    virtual std::shared_ptr<TObject> Clone() const;
//
//    template <typename CastToTy>
//    CastToTy* CastTo() noexcept;
//
//    template <typename CastToTy>
//    bool IsCastable() noexcept;
