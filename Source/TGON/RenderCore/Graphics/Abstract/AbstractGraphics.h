/*
* Author : Cha Junho
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Platform/Config/Build.h"
#include "../TGraphicsType.h"


namespace tgon
{


class TGON_API AbstractGraphics : 
	private boost::noncopyable
{
protected:
	/*
		Cons/Destructor
	*/
	explicit AbstractGraphics( class TWindow* deviceWindow );
	
	virtual ~AbstractGraphics( ) = default;

	AbstractGraphics( const AbstractGraphics& ) = delete;

	/*
		Operators
	*/
	AbstractGraphics& operator=( const AbstractGraphics& ) = delete;


public:
	/*
		Commands
	*/
	// Begin scene rendering. Return true if device can render.
	virtual bool BeginScene( ) = 0;

	// End scene rendering. This function must be called after BeginScene
	virtual bool EndScene( ) = 0;

	// Clear the back buffer scene.
	virtual bool Clear( ) = 0;

	// Draw the back buffer to visible screen.
	virtual bool Present( ) = 0;


	/*
		Sets
	*/
	void SetClearColor( uint32_t clearColor );

	virtual void SetCullMode( TCullMode cullMode ) = 0;


	/*
		Gets
	*/
	//
	class TWindow* GetDeviceWindow( );
	
	// Get owner window's screen width
	int32_t GetBackBufferWidth( ) const;

	// Get owner window's screen height
	int32_t GetBackBufferHeight( ) const;

	//
	uint32_t GetClearColor( ) const;

	//
	TCullMode GetCullMode( ) const;


protected:
	int32_t m_backBufferWidth;

	int32_t m_backBufferHeight;

	class TWindow* m_deviceWindow;

	uint32_t m_clearColor;

	TCullMode m_currMode;
};


inline void AbstractGraphics::SetClearColor( uint32_t clearColor )
{
	m_clearColor = clearColor;
}

inline uint32_t AbstractGraphics::GetClearColor( ) const
{
	return m_clearColor;
}

inline void AbstractGraphics::SetCullMode( TCullMode cullMode )
{
	m_currMode = cullMode;
}

inline TCullMode AbstractGraphics::GetCullMode( ) const
{
	return m_currMode;
}

inline class TWindow* AbstractGraphics::GetDeviceWindow( )
{
	return m_deviceWindow;
}

inline int32_t AbstractGraphics::GetBackBufferWidth( ) const
{
	return m_backBufferWidth;
}

inline int32_t AbstractGraphics::GetBackBufferHeight( ) const
{
	return m_backBufferHeight;
}


}
