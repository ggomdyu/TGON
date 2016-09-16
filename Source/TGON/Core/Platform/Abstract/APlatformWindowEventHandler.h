/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"
#include <cstdint>


namespace tgon
{


enum class MouseType
{
	Left,
	Middle,
	Right,
};

class TGON_API AWindowEventHandler
{
	//
	// Event handlers
	//
public:
	virtual void OnMove( int32_t x, int32_t y ) {}
	virtual void OnResize( int32_t width, int32_t height ) {}
	virtual void OnMouseMove( int32_t x, int32_t y ) {}
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnMouseUp( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnMouseDoubleClick( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnRawMouseMove( int32_t x, int32_t y ) {}
	virtual void OnRawMouseDown( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnRawMouseUp( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual bool OnGetFocus( ) { return true; }
	virtual bool OnLoseFocus( ) { return true; }

	/*
	 * @note	Called when window has begun closing.
	 * @return	Return true if you want to keep close.
	*/
	virtual bool OnDestroy( ) { return true; }


	//
	// Ctor/Dtor
	//
public:
	AWindowEventHandler( ) = default;
	virtual ~AWindowEventHandler( ) = default;

};


}