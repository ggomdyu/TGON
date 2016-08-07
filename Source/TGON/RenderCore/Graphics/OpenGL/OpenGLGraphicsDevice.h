/*
* Author : Kim Taewoo
* Date : 04/26/2015
* Latest author : Cha Junho
* Latest date : 01/17/2016
*/


#pragma once
#include "../Abstract/AbstractGraphicsDevice.h"


namespace tgon
{


class OpenGLGraphicsDevice;
using GraphicsDeviceImpl = OpenGLGraphicsDevice;

class TGON_API OpenGLGraphicsDevice :
	public AbstractGraphicsDevice
{
protected:
	/*
		Cons/Destructor
	*/
	explicit OpenGLGraphicsDevice( /*In*/ TWindow* deviceWindow, /*In*/ const GraphicsProperty& grpProp );
	
	OpenGLGraphicsDevice( const OpenGLGraphicsDevice& ) = delete;

	virtual ~OpenGLGraphicsDevice( ) = default;

	/*
		Operators
	*/
	OpenGLGraphicsDevice& operator=( const OpenGLGraphicsDevice& ) = delete;


public:
	/*
		Command
	*/
	// Begin scene rendering. Return true if device can render.
	virtual bool BeginScene( ) override;
	
	// End scene rendering. This function must be called after BeginScene
	virtual bool EndScene( ) override;
	
	// Clear the back buffer scene.
	virtual bool Clear( ) override;

	// Draw the back buffer to visible screen.
	virtual bool Present( ) override;

	//
	virtual void DrawPrimitive( TPrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount ) override;


	/*
		Sets
	*/
	virtual void SetCullMode( TCullMode cullMode ) override;
	
	virtual void EnableDepthBuffer( bool isEnable ) override;
	

	/*
		Gets
	*/


	/*
		Internal works
	*/
private:
#if BOOST_OS_WINDOWS
	void CreateWin32OpenGL( TWindow* deviceWindow, uint32_t colorDepthBits );
#endif
	void CreateOpenGLInstance( );
	
	/*
		Private variables
	*/
private:
#if BOOST_OS_WINDOWS
	HDC m_dcHandle;
#endif

	TPrimitiveType m_drawPrimitiveType;
};


inline void OpenGLGraphicsDevice::DrawPrimitive( TPrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount )
{
	m_drawPrimitiveType = primitiveType;

}

inline void OpenGLGraphicsDevice::SetCullMode( TCullMode cullMode )
{
	m_currMode = m_currMode;

	//if ( cullMode == TCullMode::kCW )
	//{
	//	m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CW );
	//}
	//else if ( cullMode == TCullMode::kCCW )
	//{
	//	m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW );
	//}
	//else if ( cullMode == TCullMode::kNone )
	//{
	//	m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE );
	//}
}

inline void tgon::OpenGLGraphicsDevice::EnableDepthBuffer( bool isEnable )
{
	//m_d3dDevice->SetRenderState( D3DRS_ZENABLE, ( isEnable ) ? D3DZB_TRUE : D3DZB_FALSE );
}


}
