/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Config/Build.h"

#include <cstdint>


namespace tgon
{


enum class TMouseType
{
	kLeft,
	kMiddle,
	kRight,
};

class TGON_API AbstractWindowEventHandler
{
/*
	Event handlers
*/
public:
	virtual void OnMove( int32_t x, int32_t y );

	virtual void OnResize( int32_t width, int32_t height );

	virtual void OnMouseMove( int32_t x, int32_t y );

	virtual void OnMouseDown( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnMouseUp( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnMouseDoubleClick( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnRawMouseMove( int32_t x, int32_t y );
	
	virtual void OnRawMouseDown( int32_t x, int32_t y, TMouseType mouseType );
	
	virtual void OnRawMouseUp( int32_t x, int32_t y, TMouseType mouseType );

	//
	// Called when window has begun closing.
	//
	// @return If you want to keep close, return true.
	//
	virtual bool OnDestroy( );


	/*
		Cons/Destructor
	*/
public:
	AbstractWindowEventHandler( ) = default;

	virtual ~AbstractWindowEventHandler( ) = default;

};


inline void AbstractWindowEventHandler::OnMove( int32_t x, int32_t y )
{
}

inline void AbstractWindowEventHandler::OnResize( int32_t width, int32_t height )
{
}

inline void AbstractWindowEventHandler::OnMouseMove( int32_t x, int32_t y )
{
}

inline void AbstractWindowEventHandler::OnMouseDown( int32_t x, int32_t y, TMouseType mouseType )
{
}

inline void AbstractWindowEventHandler::OnMouseUp( int32_t x, int32_t y, TMouseType mouseType )
{
}

inline void AbstractWindowEventHandler::OnMouseDoubleClick( int32_t x, int32_t y, TMouseType mouseType )
{
}

inline void AbstractWindowEventHandler::OnRawMouseMove( int32_t x, int32_t y )
{
}

inline void AbstractWindowEventHandler::OnRawMouseDown( int32_t x, int32_t y, TMouseType mouseType )
{
}

inline void AbstractWindowEventHandler::OnRawMouseUp( int32_t x, int32_t y, TMouseType mouseType )
{
}

inline bool AbstractWindowEventHandler::OnDestroy( )
{
	return true;
}


}