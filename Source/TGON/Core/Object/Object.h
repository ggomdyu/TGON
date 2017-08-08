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
	using Super = void;
	using This = Object;

/* @section Ctor/Dtor */
public:
    Object() = default;
	virtual ~Object() = default;

/* @section Public method */
public:
	virtual std::size_t GetTypeHashCode() const = 0;
    
    virtual const char* GetTypeName() const noexcept = 0;
};

} /* namespace object */
} /* namespace tgon */

#define TGON_OBJECT(classType)\
    using Super = This;\
    using This = classType;\
    \
    virtual std::size_t GetTypeHashCode() const noexcept override\
    {\
        return GetTypeInfo().GetHashCode();\
    }\
    virtual const char* GetTypeName() const noexcept override\
    {\
        return GetTypeInfo().GetName();\
    }\
    static const tgon::object::TypeInfo& GetTypeInfo() noexcept\
    {\
        static tgon::object::TypeInfo typeInfo(#classType);\
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
