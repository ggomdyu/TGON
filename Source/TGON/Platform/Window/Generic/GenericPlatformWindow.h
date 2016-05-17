/*
* 작성자 : 차준호
* 작성일 : 2016-01-09
* 최종 수정 : 
* 최종 수정일 :
*/

#pragma once
#include "../../Compiler/SyntaxCompatible.hpp"
#include <string>
#include <stdint.h>


namespace tgon {


class IWindowInterface
{
public:
	virtual void	Show() 		{}
	virtual void	Hide() 		{}
	virtual void	Maximize() 	{}
	virtual void	Minimize() 	{}
	virtual void	BringToTop() 	{}
	virtual void	Quit()  = 0;

	virtual void	SetPosition( const int32_t x, const int32_t y )	 {}
	virtual void	SetScale( const int32_t width, const int32_t height )  {}
	virtual void	SetCaption( const wchar_t* const src )  {}
	virtual void	SetCapture( )  {}

	virtual void	GetPosition( int32_t* const x, int32_t* const y ) const  {}
	virtual void	GetScale( int32_t* const width, int32_t* const height ) const  {}
	virtual void*	GetCapture( )  { return nullptr; }
	virtual std::string  GetCaption( ) const  = 0;

protected:
	IWindowInterface( ) {}
	virtual ~IWindowInterface( ) = 0 {};
};


}