/**
 * filename Object.h
 * author   ggomdyu
 * since    03/22/2016
 */

#pragma once
#include <cstdint>
#include <string>

#include "../Platform/TConfig.h"
#include "TTypeInfo.h"

namespace tgon
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
	virtual ~TObject();

/**
 * @section Public command methods
 */
public:
    template <typename CastTy>
    bool CastTo() noexcept;
    
/**
 * @section Get methods
 */
public:
    /* @brief   */
    virtual std::shared_ptr<TObject> Clone() const;

    template <typename CastTy>
    bool IsCastable() noexcept;

	/* @return	Hash value of the type name. */
	virtual uint32_t GetHashCode() const noexcept = 0;
	
    /* @return	The type name */
    virtual const std::string& GetName() const noexcept = 0;
};

template<typename CastTy>
inline bool TObject::IsCastable() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
    while()
#endif
    return dynamic_cast<CastTy>(this);
}

template<typename CastTy>
inline bool TObject::CastTo() noexcept
{
#if TGON_RTTI_ENABLED
    // ToDo : Implement RTTI
#endif
    return dynamic_cast<CastTy>(this) ? reinterpret_cast<CastTy>(this) : nullptr;
}

} /* namespace tgon */

#define TGON_MAKE_OBJECT_INTERFACE(classType)\
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
    static const TTypeInfo& GetTypeInfo() noexcept\
    {\
        static TTypeInfo typeInfo(#classType);\
        return typeInfo;\
    }