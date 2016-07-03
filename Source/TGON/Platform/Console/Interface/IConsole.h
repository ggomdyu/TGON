/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IConsole : 
	private boost::noncopyable
{
public:
	/*
		Cons/Destructor
	*/
	IConsole( ) = delete;

	virtual ~IConsole( ) = delete;


	/*
		Commands
	*/
	template<class _Ty>
	static void Write( _Ty&& str ) {}

	template <std::size_t N>
	static void Write( _In_ const char( &str )[N], std::true_type ) {}

	static void Write( _In_ const char* str, std::false_type ) {}

	template<class _Ty>
	static void Write( const _Ty& str, std::false_type ) {}

	template <std::size_t N>
	static void Write( _In_ const wchar_t( &str )[N], std::true_type ) {}

	static void Write( _In_ const wchar_t* str, std::false_type ) {}
};


}