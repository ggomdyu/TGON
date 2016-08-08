/*
* Author : Cha Junho
* Date : 04/19/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/Build.h"

#include <string>


namespace tgon
{


class TGON_API TType final
{
/*
	Cons/Destructor
*/
public:
	explicit TType( const std::string& name );

	~TType( );


/*
	Gets
*/
public:
	uint32_t GetHashCode( ) const;

	const std::string& GetName( ) const;

/*
	Private variables
*/
private:
	const uint32_t m_hashCode;

	const std::string m_name;
};


inline uint32_t TType::GetHashCode( ) const
{
	return m_hashCode;
}

inline const std::string& TType::GetName( ) const
{
	return m_name;
}


}