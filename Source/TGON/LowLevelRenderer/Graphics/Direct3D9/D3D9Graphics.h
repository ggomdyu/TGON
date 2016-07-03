/*
* Author : Kim Taewoo
* Date : 04/26/2015
* Latest author : Cha Junho
* Latest date : 01/17/2016
*/


#pragma once
#include "../Abstract/AbstractGraphics.h"
#include "D3D9Fwd.h"


namespace tgon
{


using GraphicsImpl = class D3D9Graphics;

class TGON_API D3D9Graphics : 
	private AbstractGraphics
{
public:
	D3D9Graphics( );
	
	virtual ~D3D9Graphics( );

public:
	/*
		Command
	*/
	//void DrawLine( );
	
	/*
		Sets
	*/

	/*
		Gets
	*/
	const SpD3D9Ex& GetD3D( ) const;

	const SpD3D9DeviceEx& GetD3DDevice( ) const;
	
private:
	void InitDevice( );

private:
	shared_comptr<IDirect3D9Ex> m_d3d;

	shared_comptr<IDirect3DDevice9Ex> m_d3dDevice;


};


}


inline const tgon::SpD3D9Ex& tgon::D3D9Graphics::GetD3D( ) const
{
	return m_d3d;
}

const tgon::SpD3D9DeviceEx& tgon::D3D9Graphics::GetD3DDevice( ) const
{
	return m_d3dDevice;
}