/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include "TypeId.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TObject 
{
public:
	static bool Equals( const TObject*, const TObject* );
	static bool Equals( const TObject&, const TObject& );
	bool Equals( const TObject* );
	bool Equals( const TObject& );

public:
	/*
		Gets
	*/
	virtual uint32_t GetHashCode( ) const = 0;
	virtual const char* GetName( ) const = 0;

public:
	TObject( ) {}
	virtual ~TObject( ) = 0 {}
};

inline bool TObject::Equals(
	const TObject* lhs,
	const TObject* rhs )
{
	return ( lhs->GetHashCode( ) == rhs->GetHashCode( ));
}

inline bool TObject::Equals(
	const TObject& lhs,
	const TObject& rhs )
{
	return ( lhs.GetHashCode( ) == rhs.GetHashCode( ));
}

inline bool TObject::Equals(
	const TObject* rhs )
{
	return ( this->GetHashCode( ) == rhs->GetHashCode( ) );
}

inline bool TObject::Equals( 
	const TObject& rhs )
{
	return ( this->GetHashCode( ) == rhs.GetHashCode( ) );

}


}


#define TGON_OBJECT( myType, baseType )\
	using type = myType;\
	using base_type = baseType;\
	\
	virtual uint32_t GetHashCode( ) const override\
	{\
		return GetTypeId( ).GetHashCode( );\
	}\
	\
	virtual const char* GetName( ) const override\
	{\
		return GetTypeId( ).GetName( );\
	}\
	\
	static const tgon::TypeId& GetTypeId( )\
	{\
		static tgon::TypeId typeID( #myType );\
		return typeID;\
	}