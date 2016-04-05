/*
* 작성자 : 차준호
* 작성일 : 2016-03-23
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "../../Compiler/SyntaxCompatible.hpp"
#include <string>
#include <iostream>


namespace tgon
{


class IConsoleInterface
{
protected:
	IConsoleInterface( ) {};
	virtual ~IConsoleInterface( ) = 0 {};

public:
	virtual void WriteLine( )  = 0;
	
	virtual void SetColor( uint32_t color )  {}
	virtual void SetSize( uint32_t size )  {}

};

class ConsoleBaseImpl
{
protected:
	ConsoleBaseImpl() {};
	virtual ~ConsoleBaseImpl() {};

protected:
	template<class T>
	TGON_FORCEINLINE void	FillBuffer( const T& arg ) ;
	TGON_FORCEINLINE void	FillBuffer( const wchar_t* arg ) ;

	const wchar_t*	GetBuffer( ) const ;
	size_t			GetBufferLength( ) const ;
	void			ClearBuffer( ) ;

private:
	std::wstring	m_buf;
};


}


#include "GenericPlatformConsole.inl"