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


using GraphicsImpl = class D3D9Graphics;

class TGON_API D3D9Graphics : 
	public AbstractGraphics
{
protected:
	/*
		Cons/Destructor
	*/
	explicit D3D9Graphics( class TWindow* deviceWindow );
	
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
	virtual bool BeginScene( );
	
	// End scene rendering. This function must be called after BeginScene
	virtual bool EndScene( );
	
	// Clear the back buffer scene.
	virtual bool Clear( );

	// Draw the back buffer to visible screen.
	virtual bool Present( );

	//
	void DrawPrimitive( TPrimitiveType primitiveType, uint32_t startVertex, uint32_t primitiveCount );


	/*
		Sets
	*/

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


}