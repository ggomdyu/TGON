/**
 * @filename    TObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include "TTypeInfo.h"
#include "Core/Platform/TConfig.h"

namespace tgon
{
namespace object
{

class TGON_API TObject 
{
public:
	using Super = void;
	using This = TObject;

/**
 * @section Ctor/Dtor
 */
public:
	TObject() = default;
	virtual ~TObject() = default;

/**
 * @section Public method
 */
public:
    virtual std::shared_ptr<TObject> Clone() const;

    template <typename CastToTy>
    CastToTy* CastTo() noexcept;

    template <typename CastToTy>
    bool IsCastable() noexcept;

public:
	/* @return	Hash value of the type name. */
	virtual std::size_t GetHashCode() const noexcept = 0;
	
    /* @return	The type name */
    virtual const std::string& GetTypeName() const noexcept = 0;
};

template<typename CastToTy>
inline bool TObject::IsCastable() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
    while()
#else
    return dynamic_cast<CastToTy>(this);
#endif
}

template<typename CastToTy>
inline CastToTy* TObject::CastTo() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
#else
    return dynamic_cast<CastToTy>(this);
#endif
}

} /* namespace object */
} /* namespace tgon */

#define TGON_CREATE_OBJECT_INTERFACE(classType)\
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
    static const object::TTypeInfo& GetTypeInfo() noexcept\
    {\
        static object::TTypeInfo typeInfo(#classType);\
        return typeInfo;\
    }