/**
 * @filename    TObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <cstdint>
#include <string>

#include "Core/Platform/TConfig.h"
#include "TTypeInfo.h"

namespace tgon {
namespace object {

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
 * @section Public command method
 */
public:
    virtual std::shared_ptr<TObject> Clone() const;

    template <typename CastTy>
    bool CastTo() noexcept;

    template <typename CastTy>
    bool IsCastable() noexcept;

/**
 * @section Get method
 */
public:
	/* @return	Hash value of the type name. */
	virtual std::size_t GetHashCode() const noexcept = 0;
	
    /* @return	The type name */
    virtual const std::string& GetName() const noexcept = 0;
};

template<typename CastTy>
inline bool TObject::IsCastable() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
    while()
#else
    return dynamic_cast<CastTy>(this);
#endif
}

template<typename CastTy>
inline bool TObject::CastTo() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
#else
    return dynamic_cast<CastTy>(this);
#endif
}

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
	virtual const std::string& GetName() const noexcept override\
    {\
        return classType::GetTypeInfo().GetName();\
    }\
    static const object::TTypeInfo& GetTypeInfo() noexcept\
    {\
        static object::TTypeInfo typeInfo(#classType);\
        return typeInfo;\
    }