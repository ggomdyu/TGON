/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../PlatformInclude.h"
#include <cstdint>


namespace tgon
{


enum class EMouseType
{
	Left,
	Middle,
	Right,
};

class TGON_API IWindowEventHandler
{
	//
	// Event handlers
	//
public:
	virtual void OnMove( int32_t x, int32_t y ) = 0;
	virtual void OnResize( int32_t width, int32_t height ) = 0;
	virtual void OnMouseMove( int32_t x, int32_t y ) = 0;
	virtual void OnMouseDown( int32_t x, int32_t y, EMouseType mouseType ) = 0;
	virtual void OnMouseUp( int32_t x, int32_t y, EMouseType mouseType ) = 0;
	virtual void OnMouseDoubleClick( int32_t x, int32_t y, EMouseType mouseType ) = 0;
	virtual void OnRawMouseMove( int32_t x, int32_t y ) = 0;
	virtual void OnRawMouseDown( int32_t x, int32_t y, EMouseType mouseType ) = 0;
	virtual void OnRawMouseUp( int32_t x, int32_t y, EMouseType mouseType ) = 0;
	virtual bool OnGetFocus( ) = 0;
	virtual bool OnLoseFocus( ) = 0;

	/*
	 * @note	Called when window has begun closing.
	 * @return	Return true if you want to keep close.
	*/
	virtual bool OnDestroy( ) = 0;

};


}