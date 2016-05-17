/*
* Author : Junho-Cha
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <string>
#include "../Core/Math/TMath.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TTypeId
{
public:
	TTypeId( const char* name ) :
		m_name( name ),
		m_hashCode( TMath::GenerateHash( name ))
	{
	}

	const char* name( ) const;
	uint32_t hash_code( ) const;

private:
	std::string m_name;
	uint32_t m_hashCode;
};


inline const char* TTypeId::name( ) const
{
	return m_name.c_str( );
}

inline uint32_t TTypeId::hash_code( ) const
{
	return m_hashCode;
}


}