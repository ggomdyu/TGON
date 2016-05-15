/*
* Author : Junho-Cha
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <stdint.h>


namespace tgon
{


class TStringHash
{
public:
	TStringHash( const char* str );
	~TStringHash( );

	uint32_t GetHash( ) const;

private:
	uint32_t m_hash;
};

inline uint32_t tgon::TStringHash::GetHash( ) const
{
	return m_hash;
}


}