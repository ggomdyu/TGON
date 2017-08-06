/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include "TypeInfo.h"

#include "Core/Hash/Hash.h"
#include "Core/Utility/Array.h"
#include "Core/Platform/Config.h"

namespace tgon
{
namespace object
{

class TGON_API Object
{
/* @section Type definition */
public:
	using Super = void;
	using This = Object;

/* @section Ctor/Dtor */
public:
    Object() = default;
	virtual ~Object() = default;

/* @section Public method */
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
    virtual std::size_t GetHashCode() const override\
    {\
        return tgon::hash::x65599Hash(#classType);\
    }\
    virtual const char* GetTypeName() const noexcept override\
    {\
        static constexpr const char* typeName = #classType;\
        return typeName;\
    }

// Todo: Implement interface's below
//    virtual std::shared_ptr<TObject> Clone() const;
//
//    template <typename CastToTy>
//    CastToTy* CastTo() noexcept;
//
//    template <typename CastToTy>
//    bool IsCastable() noexcept;
