/*
* Author : Cha Junho
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Core/Platform/OSAL/PlatformInclude.h"

#include <memory>
#include <boost/noncopyable.hpp>

#include "../Core/Platform/OSAL/PlatformWindow.h"
#include "../GraphicsProperty.h"
#include "../GraphicsType.h"
#include "AbstractGraphicsDeviceEventHandler.h"


namespace tgon
{


class TGON_API AbstractGraphicsDevice : 
	private boost::noncopyable
{
/*
	Ctor/Dtor
*/
protected:
	//
	// @note Constructor
	// @param deviceWindow Window which you want to present 3D space
	//
	explicit AbstractGraphicsDevice( /*In*/ TPlatformWindow* deviceWindow );
	
	AbstractGraphicsDevice( const AbstractGraphicsDevice& rhs ) = delete;

	virtual ~AbstractGraphicsDevice( ) = default;


	/*
		Operators
	*/
	//
	// Copy assignment operator
	//
	// @param rhs ignore, DO NOT CALL this
	//
	AbstractGraphicsDevice& operator=( const AbstractGraphicsDevice& ) = delete;

	
	/*
		Commands
	*/
public:
	//
	// Begin scene rendering. Return true if device can render.
	//
	// @return Return true on success.
	//
	virtual bool BeginScene( ) = 0;

	//
	// End scene rendering. This function must be called after BeginScene
	//
	// @return Return true on success.
	//
	virtual bool EndScene( ) = 0;

	//
	// Clear the back buffer scene.
	//
	// @return Return true on success.
	//
	virtual bool Clear( ) = 0;

	//
	// @note Draw the back buffer to visible screen.
	// @return Return true on success.
	//
	virtual bool Present( ) = 0;

	//
	// @note Draw geometry data
	// @param primitiveType 
	// @param startVertex 
	// @param primitiveCount 
	//
	virtual void DrawPrimitive( PrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount ) = 0;


	/*
		Sets
	*/
	//
	// @note Set the graphics event handler.
	// @param eventHandler Event handler which you want to set
	//
	void SetEventHandler( const std::shared_ptr<AbstractGraphicsDeviceEventHandler>& eventHandler );

	//
	// Set the back-buffer clear color.
	// Device will clear back-buffer as this color before it draws a new image or etc. Use in Clear( ).
	//
	// @param clearColor Background clear color that contains color components each of 8 bits( 255-255-255-255 ).
	//
	void SetClearColor( uint32_t clearColor );

	//
	// Set the culling mode.
	//
	// @param 
	//
	virtual void SetCullMode( TCullMode cullMode ) = 0;

	//
	virtual void EnableDepthBuffer( bool isEnable ) = 0;


	/*
		Gets
	*/
	//
	// Return current event handler.
	//
	// @return AbstractGraphicsDeviceEventHandler as shared_ptr type.
	//
	const std::shared_ptr<AbstractGraphicsDeviceEventHandler>& GetEventHandler( ) const;

	//
	// @return Return present window target.
	//
	TPlatformWindow* GetDeviceWindow( );
	
	//
	// @return Return owner window's screen width
	//
	int32_t GetBackBufferWidth( ) const;

	//
	// @return Return owner window's screen height
	// 
	int32_t GetBackBufferHeight( ) const;

	//
	// @return Return device's background clear color.
	//
	uint32_t GetClearColor( ) const;

	//
	// @return Return device's culling mode.
	//
	TCullMode GetCullMode( ) const;


/*
	Variables
*/
protected:
	TPlatformWindow* m_deviceWindow;

	std::shared_ptr<AbstractGraphicsDeviceEventHandler> m_eventHandler;

	int32_t m_backBufferWidth;
	
	int32_t m_backBufferHeight;
	
	uint32_t m_clearColor;
	
	TCullMode m_currMode;
};


inline void AbstractGraphicsDevice::SetEventHandler( const std::shared_ptr<AbstractGraphicsDeviceEventHandler>& eventHandler )
{
}

inline void AbstractGraphicsDevice::SetClearColor( uint32_t clearColor )
{
	m_clearColor = clearColor;
}

inline uint32_t AbstractGraphicsDevice::GetClearColor( ) const
{
	return m_clearColor;
}

inline void AbstractGraphicsDevice::SetCullMode( TCullMode cullMode )
{
	m_currMode = cullMode;
}

inline TCullMode AbstractGraphicsDevice::GetCullMode( ) const
{
	return m_currMode;
}

inline const std::shared_ptr<AbstractGraphicsDeviceEventHandler>& AbstractGraphicsDevice::GetEventHandler( ) const
{
	return m_eventHandler;
}

inline TPlatformWindow* AbstractGraphicsDevice::GetDeviceWindow( )
{
	return m_deviceWindow;
}

inline int32_t AbstractGraphicsDevice::GetBackBufferWidth( ) const
{
	return m_backBufferWidth;
}

inline int32_t AbstractGraphicsDevice::GetBackBufferHeight( ) const
{
	return m_backBufferHeight;
}


}
