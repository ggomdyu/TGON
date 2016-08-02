/*
* Author : Kim Taewoo
* Date : 04/26/2015
* Latest author : Cha Junho
* Latest date : 01/17/2016
*/


#pragma once
#include "../Abstract/AbstractGraphics.h"

#include <d3d9.h>
#include "D3D9Fwd.h"


namespace tgon
{


class D3D9Graphics;
using GraphicsImpl = D3D9Graphics;

class TGON_API D3D9Graphics : 
	public AbstractGraphics
{
protected:
	/*
		Cons/Destructor
	*/
	explicit D3D9Graphics( TWindow* deviceWindow, bool isWindowed );
	
	D3D9Graphics( const D3D9Graphics& ) = delete;

	virtual ~D3D9Graphics( ) = default;

	/*
		Operators
	*/
	D3D9Graphics& operator=( const D3D9Graphics& ) = delete;


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
	const SpD3D9Ex& GetD3D( ) const;

	const SpD3D9DeviceEx& GetD3DDevice( ) const;
	

private:
	/*
		Internal works
	*/

	// Initialize IDirect3D9Ex and Caps
	void InitD3DInterface( );

	// Initialize IDirect3DDevice9Ex
	void InitD3DDevice( );


private:
	shared_comptr<IDirect3D9Ex> m_d3d;

	shared_comptr<IDirect3DDevice9Ex> m_d3dDevice;

	std::unique_ptr<D3DCAPS9> m_deviceCaps;
};


inline const SpD3D9Ex& D3D9Graphics::GetD3D( ) const
{
	return m_d3d;
}

inline const SpD3D9DeviceEx& D3D9Graphics::GetD3DDevice( ) const
{
	return m_d3dDevice;
}

inline void D3D9Graphics::DrawPrimitive( TPrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount )
{
	m_d3dDevice->DrawPrimitive(
		static_cast<D3DPRIMITIVETYPE>( primitiveType ),
		startVertex,
		primitiveCount
	);
}

inline void D3D9Graphics::SetCullMode( TCullMode cullMode )
{
	m_currMode = m_currMode;

	if ( cullMode == TCullMode::kCW )
	{
		m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CW );
	}
	else if ( cullMode == TCullMode::kCCW )
	{
		m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW );
	}
	else if ( cullMode == TCullMode::kNone )
	{
		m_d3dDevice->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL::D3DCULL_NONE );
	}
}

inline void tgon::D3D9Graphics::EnableDepthBuffer( bool isEnable )
{
	m_d3dDevice->SetRenderState( D3DRS_ZENABLE, ( isEnable ) ? D3DZB_TRUE : D3DZB_FALSE );
}


}
