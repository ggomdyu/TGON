/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


enum class TMouseType
{
	kLeft,
	kMiddle,
	kRight,
};

class AbstractWindowEventHandler
{
public:
	/*
		Cons/Destructor
	*/
	AbstractWindowEventHandler( ) = default;

	virtual ~AbstractWindowEventHandler( )
	{
	}


	/*
		Event handlers
	*/
	virtual bool OnMove( int32_t x, int32_t y );

	virtual bool OnResize( int32_t width, int32_t height );

	virtual void OnMouseMove( int32_t x, int32_t y );

	virtual void OnMouseDown( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnMouseUp( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnMouseDoubleClick( int32_t x, int32_t y, TMouseType mouseType );

	virtual void OnRawMouseMove( int32_t x, int32_t y );
	
	virtual void OnRawMouseDown( int32_t x, int32_t y, TMouseType mouseType );
	
	virtual void OnRawMouseUp( int32_t x, int32_t y, TMouseType mouseType );

	virtual bool OnDestroy( );
};


inline bool AbstractWindowEventHandler::OnMove( int32_t x, int32_t y )
{
	return false;
}

inline bool AbstractWindowEventHandler::OnResize( int32_t width, int32_t height )
{
	return false;
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
	return false;
}


}