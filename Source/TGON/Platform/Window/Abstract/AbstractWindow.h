/*
* Author : Cha Junho
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include "../WindowStyle.h"


namespace tgon
{


class TGON_API AbstractWindow : 
	private boost::noncopyable
{
protected:
	/*
		Cons/Destructor
	*/
	AbstractWindow( );

	virtual ~AbstractWindow( ) = 0;


public:
	/*
		Commands
	*/
	virtual void Show( ) {}

	virtual void Hide( ) {}

	virtual void Quit( ) {}

	virtual void Maximize( ) {}

	virtual void Minimize( ) {}

	virtual void BringToTop( ) {}

	virtual void Flash( ) {}


	/*
		Sets
	*/
	virtual void SetPosition( int32_t x, int32_t y ) {};

	virtual void SetScale( int32_t width, int32_t height ) {};

	virtual void SetCaption( const wchar_t* src ) {};

	/*
		Gets
	*/
	virtual void GetPosition( int32_t* x, int32_t* y ) const {};

	virtual void GetSize( int32_t* width, int32_t* height ) const {};

	virtual void GetCaption( wchar_t* caption ) const {}

	virtual bool IsDestroyed( ) const { return false; }


	/*
		Event handlers
	*/
	virtual void OnIdle( ) {}

};


}