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
	private AbstractGraphics
{
protected:
	explicit D3D9Graphics( const TWindow& owner );
	
public:
	virtual ~D3D9Graphics( ) = default;

	explicit D3D9Graphics( const D3D9Graphics& ) = delete;

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

	/*
		Sets
	*/

	/*
		Gets
	*/
	const SpD3D9Ex& GetD3D( ) const;

	const SpD3D9DeviceEx& GetD3DDevice( ) const;
	
private:
	// Initialize IDirect3D9Ex and Caps
	void InitD3DInterface( );

	// Initialize IDirect3DDevice9Ex
	void InitD3DDevice( );

private:
	shared_comptr<IDirect3D9Ex> m_d3d;

	shared_comptr<IDirect3DDevice9Ex> m_d3dDevice;

	std::unique_ptr<D3DCAPS9> m_deviceCaps;

	const TWindow& m_ownerWindow;

	const D3DCOLOR m_clearColor;
};


}


inline const tgon::SpD3D9Ex& tgon::D3D9Graphics::GetD3D( ) const
{
	return m_d3d;
}

inline const tgon::SpD3D9DeviceEx& tgon::D3D9Graphics::GetD3DDevice( ) const
{
	return m_d3dDevice;
}