/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include <stdint.h>

#include "TTypeId.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TObject 
{
public:
	/*
		@ Cons/Destructor
	*/
	TObject( ) {}
	virtual ~TObject( ) = 0 {}

	static bool Equals( const TObject&, const TObject& );
	static bool Equals( const TObject*, const TObject* );

	/*
		@ Gets
	*/
public:
	virtual uint32_t GetHashCode( ) const = 0;
	virtual const char* GetName( ) const = 0;
};

inline bool TObject::Equals(
	const TObject& lhs,
	const TObject& rhs )
{
	return ( lhs.GetHashCode( ) == rhs.GetHashCode( ));
}

inline bool TObject::Equals(
	const TObject* lhs,
	const TObject* rhs )
{
	return ( lhs->GetHashCode( ) == rhs->GetHashCode( ));
}


}


#define TGON_OBJECT( myType, baseType )\
	using type = myType;\
	using base_type = baseType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return GetTypeId( ).hash_code( );\
	}\
	\
	virtual const char* GetName( ) const override\
	{\
		return GetTypeId( ).name( );\
	}\
	\
	static const tgon::TTypeId& GetTypeId( )\
	{\
		static tgon::TTypeId typeID( #myType );\
		return typeID;\
	}