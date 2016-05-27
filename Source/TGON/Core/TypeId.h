/*
* Author : Junho-Cha
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Core/Math/TMath.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TypeId
{
public:
	TypeId( const char* name ) :
		m_name( name ),
		m_hashCode( TMath::GenerateHash( name ))
	{
	}
	~TypeId( ) {}

	uint32_t GetHashCode( ) const;
	const char* GetName( ) const;

private:
	uint32_t m_hashCode;
	std::string m_name;
};


inline const char* TypeId::GetName( ) const
{
	return m_name.c_str( );
}

inline uint32_t TypeId::GetHashCode( ) const
{
	return m_hashCode;
}


}