/*
* 작성자 : 차준호
* 작성일 : 2016-01-09
* 최종 수정 : 
* 최종 수정일 :
*/

#pragma once
#include "../../Config/Compiler/SyntaxCompatible.hpp"
#include <string>
#include <stdint.h>


namespace tgon {


class LayeredWindow
{
public:
	// Sets
	virtual void Show() {}
	virtual void Quit() {}
	virtual void Hide() {}
	virtual void Maximize() {}
	virtual void Minimize() {}
	virtual void BringToTop() {}
	virtual void FlashWindow() {}
	virtual void SetPosition( const int32_t x,
							  const int32_t y ) = 0;
	virtual void SetSize( const int32_t width,
						  const int32_t height ) = 0;
	virtual void SetCaption( const wchar_t* const src ) = 0;

	// Gets
	virtual bool IsQuitted( ) { return true; }
	virtual void GetPosition( int32_t* const x,
							  int32_t* const y ) const = 0;
	virtual void GetSize( int32_t* const width,
						  int32_t* const height ) const = 0;
	virtual std::wstring GetCaption( ) const = 0;

protected:
	LayeredWindow( ) {}
	virtual ~LayeredWindow( ) = 0 {};
};


}