/*
* Author : Cha Junho
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"

#include "../Math/TMath.h"


namespace tgon
{


class TGON_API TType
{
public:
	/*
		Cons/Destructor
	*/
	explicit TType( const char* name );

	~TType( );

public:
	uint32_t GetHashCode( ) const;

	const char* GetName( ) const;

private:
	uint32_t m_hashCode;

	const char* m_name;
};


inline TType::TType( const char* name ) :
	m_hashCode( TMath::GenerateHash( name )),
	m_name( name )
{
}

inline TType::~TType( )
{
}

inline uint32_t TType::GetHashCode( ) const
{
	return m_hashCode;
}

inline const char* TType::GetName( ) const
{
	return m_name;
}


}