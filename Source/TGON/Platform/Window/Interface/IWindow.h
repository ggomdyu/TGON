/*
* Author : Junho-Cha
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include <string>
#include <stdint.h>

#include <boost/noncopyable.hpp>
#include "../../../Platform/Config/Build.h"


namespace tgon
{
	

class TGON_API IWindow : 
	private boost::noncopyable
{
public:
	/*
		Commands
	*/
	virtual void SetPosition( int32_t x, int32_t y ) {};
	virtual void SetScale( int32_t width, int32_t height ) {};
	virtual void SetCaption( const wchar_t* src ) {};
	virtual void Show( ) {};
	virtual void Hide( ) {};
	virtual void Quit( ) = 0;	// Must be implemented
	virtual void Maximize( ) {};
	virtual void Minimize( ) {};
	virtual void BringToTop( ) {};
	virtual void Flash( ) {};

	virtual void GetPosition( int32_t* x, int32_t* y ) const {};
	virtual void GetSize( int32_t* width, int32_t* height ) const {};
	virtual std::wstring GetCaption( ) const { return L""; }
	virtual bool IsDestroyed( ) { return false; }


	/*
		@ Cons/Destructors
	*/
protected:
	IWindow( ) {}
	virtual ~IWindow( ) = 0 {};


	/*
		@ Internal works
	*/
private:
	virtual void LazyInitialization( ) = 0;
};


}