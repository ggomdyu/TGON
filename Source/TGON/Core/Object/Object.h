/**
 * filename Object.h
 * author   ggomdyu
 * since    03/22/2016
 */

#pragma once
#include <cstdint>
#include <string>

#include "../Platform/OSAL/PlatformInclude.h"
#include "Type.h"

namespace tgon
{

class TGON_API Object 
{
public:
	using This = Object;
	using Super = void;

/**
 * @section Ctor/Dtor
 */
public:
	Object() = default;
	virtual ~Object();
    
/**
 * @section Gets
 */
public:
    /* @brief   */
    //virtual std::shared_ptr<Object> Clone();

	/**
     * @brief   Compares dynamic bound type of two instance.
     * @return  True if both type of dynamic bound is same.
     */
	bool Equals(const Object& rhs) const noexcept;

    template <typename CastToTy>
    bool IsCastable() noexcept;

    template <typename CastToTy>
    bool CastTo() noexcept;

	/* @return	Hash value of the type name. */
	virtual uint32_t GetHashCode() const noexcept = 0;
	
    /* @return	The type name */
    virtual const std::string& GetName() const noexcept = 0;
};

template<typename CastToTy>
inline bool Object::IsCastable() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
    while()
#endif
    return dynamic_cast<CastToTy>(this);
}

template<typename CastToTy>
inline bool Object::CastTo() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
#endif
    return dynamic_cast<CastToTy>(this) ? reinterpret_cast<CastToTy>(this) : nullptr;
}

} /* namespace tgon */

#define TGON_GENERATE_OBJECT_INTERFACE(classType)\
	using Super = This;\
	using This = classType;\
	\
	virtual uint32_t GetHashCode() const noexcept override\
	{\
		return classType::GetTypeInfo().GetHashCode();\
	}\
	virtual const std::string& GetName() const noexcept override\
	{\
		return classType::GetTypeInfo().GetName();\
	}\
	static const TypeInfo& GetTypeInfo()\
	{\
		static TypeInfo typeInfo(#classType);\
		return typeInfo;\
	}