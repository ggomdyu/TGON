/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include "Core/Platform/Config.h"
#include "TypeInfo.h"

#include <cstdint>
#include <memory>
#include <string>

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
	virtual std::size_t GetHashCode() const noexcept = 0;
    
    virtual const std::string& GetTypeName() const noexcept = 0;
};

} /* namespace object */
} /* namespace tgon */

#define TGON_MAKE_OBJECT_INTERFACE(classType)\
    using Super = This;\
	using This = classType;\
	\
	virtual std::size_t GetHashCode() const noexcept override\
	{\
		return classType::GetTypeInfo().GetHashCode();\
	}\
	virtual const std::string& GetTypeName() const noexcept override\
    {\
        return classType::GetTypeInfo().GetTypeName();\
    }\
    static const object::TypeInfo& GetTypeInfo() noexcept\
    {\
        static object::TypeInfo typeInfo(#classType);\
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
