/*
* Author : Cha Junho
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TType final
{
/*
	Cons/Destructor
*/
public:
	explicit TType( const char* name );

	~TType( );

/*
	Gets
*/
public:
	uint32_t GetHashCode( ) const;

	const char* GetName( ) const;

/*
	Private variables
*/
private:
	uint32_t m_hashCode;

	const char* m_name;
};


inline uint32_t TType::GetHashCode( ) const
{
	return m_hashCode;
}

inline const char* TType::GetName( ) const
{
	return m_name;
}


}