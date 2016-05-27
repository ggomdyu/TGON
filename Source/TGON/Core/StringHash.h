/*
* Author : Junho-Cha
* Date : 05/15/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


class StringHash
{
public:
	StringHash( const char* str );
	~StringHash( );

	uint32_t GetHashCode( ) const;

private:
	uint32_t m_hashCode;
};

inline uint32_t tgon::StringHash::GetHashCode( ) const
{
	return m_hashCode;
}


}