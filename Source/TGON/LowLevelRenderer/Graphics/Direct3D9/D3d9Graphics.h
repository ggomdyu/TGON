/*
* Author : Taewoo-Kim
* Date : 04/26/2015
* Latest author : Junho-Cha
* Latest date : 01/17/2016
*/


#pragma once
#include "../Interface/IGraphics.h"
#include "../../../Platform/Slate/PlatformFwd.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "D3d9Fwd.h"


/*
	Import libraries
*/
#pragma comment( lib, "d3d9.lib" )
#if defined( _DEBUG ) || defined( DEBUG )
	#pragma comment( lib, "d3dx9d.lib" )
#else
	#pragma comment( lib, "d3dx9.lib" )
#endif


namespace tgon
{


class D3d9Graphics;
typedef D3d9Graphics GraphicsImpl;

class D3d9Graphics : private IGraphics
{
	/*
		@ Commands
	*/
public:
	virtual void BeginScene( ) override;
	virtual void EndScene( ) override;

	IDirect3D9Ex* GetD3d( );
	IDirect3DDevice9Ex* GetD3dDevice( );


	/*
		@ Cons/Destructors
	*/
protected:
	explicit D3d9Graphics( const SpTWindow&, const struct GraphicsStyle& );
public:
	virtual ~D3d9Graphics( );


	/*
		@ Internal work
	*/
private:
	void InitDevice( const SpTWindow&, const GraphicsStyle& );
	void InitSpriteDevice( );

	/*
		@ Private data area
	*/
private:
	SpD3d9Ex m_d3d;
	SpD3d9DeviceEx m_d3dDevice;
	SpD3d9Sprite m_d3dSprite;
	D3DCAPS9 m_deviceCaps;
};


}