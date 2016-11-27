/**
 * Author : Cha Junho
 * Date : 03/22/2016
 * Latest author :
 * Latest date :
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
 * Ctor/Dtor
 */
public:
	Object( );
	virtual ~Object( ) = 0;

/**
 * Opeators
 */
	bool operator==( const Object& ) const;
	bool operator!=( const Object& ) const;

/**
 * Commands
 */
public:
	static bool Equals( const Object&, const Object& );
	
	/**
	 * @note    Compares two instance. This can be overridden.
	 * @return  True if both refer to the same object.
	 */
	virtual bool Equals( const Object& rhs ) const;

	/** 
	 * @note            Compares two instance.
	 * @param   lhs     Left handling side
	 * @param   rhs     Right handling side
	 * @return          True if both refer to the same object.
	 */
	static bool ReferenceEquals( const Object& lhs, const Object& rhs );

/**
 * Gets
 */
	/* @return	Hash value of the type name. */
	virtual uint32_t GetHashCode( ) const = 0;
	
    /* @return	The type name */
    virtual const std::string& GetName( ) const = 0;
};

} /* namespace tgon */


#define TGON_GENERATE_OBJECT_INTERFACE( classType )\
	using Super = This;\
	using This = classType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return classType::GetTypeInfo( ).GetHashCode( );\
	}\
	virtual const std::string& GetName( ) const override\
	{\
		return classType::GetTypeInfo( ).GetName( );\
	}\
    static const TypeInfo& GetTypeInfo( )\
    {\
        static TypeInfo typeInfo( #classType );\
        return typeInfo;\
    }