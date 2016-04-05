/*
* 작성자 : 차준호
* 작성일 : 2016-03-22
* 최종 수정 :
* 최종 수정일 :
* Description :
*/

#pragma once
#include <iostream>
#include <stdint.h>
#include <string.h>
#include "../Math/TMath.h"


namespace tgon
{

//enum class TObjectType
//{
//	kGameObject,
//	kSubSystem,
//	kText,
//	kData,
//	kEtc,
//};


class TObject
{
public:
	TObject( const char* typeName,
			 const TObject* baseType ) :
		m_typeName( typeName ),
		m_typeHashCode( TMath::GenerateHash( typeName )),
		m_baseType( baseType ) {}
	
	virtual ~TObject( ) {}


	static bool	Equals( const TObject&,
						const TObject& );

	const char* GetName( ) const;
	uint32_t	GetHashCode( ) const;

private:
	const std::string	m_typeName;
	const uint32_t		m_typeHashCode;
	//const TObjectType	m_objectType;

	const TObject*		m_baseType;
};


inline bool TObject::Equals( const TObject& first,
						     const TObject& second )
{
	return ( first.GetHashCode( ) == second.GetHashCode( ));
}

inline const char* TObject::GetName( ) const
{
	return m_typeName.c_str( );
}

inline uint32_t TObject::GetHashCode( ) const
{
	return m_typeHashCode;
}



}