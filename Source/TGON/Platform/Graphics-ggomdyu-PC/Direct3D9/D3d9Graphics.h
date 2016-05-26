/*
* Author : Taewoo-Kim
* Date : 04/26/2015
* Latest author : Junho-Cha
* Latest date : 01/17/2016
*/


#pragma once
#include "../Abstract/AbstractGraphics.h"
#include "../../../Platform/Config/Build.h"
#include "../../../Platform/Slate/PlatformFwd.h"

#include <d3dx9.h>

#include "D3d9Util.h"
#include "D3d9Fwd.h"


/*
	Import libraries
*/#pragma comment( lib, "d3d9.lib" )
#if defined( _DEBUG ) || defined( DEBUG )
	#pragma comment( lib, "d3dx9d.lib" )
#else
	#pragma comment( lib, "d3dx9.lib" )
#endif



namespace tgon
{



class IDeviceDelegate
{
	virtual void OnDeviceReset( ) = 0;
	virtual void OnDeviceLost( ) = 0;
};

class TGON_API D3d9Graphics : 
	private IGraphics
{
	/*
		@ Commands
	*/
public:
	virtual void Clear( ) override;
	virtual void Begin( ) override;
	virtual void End( ) override;
	virtual void Present( ) override;

	virtual void Draw( PrimitiveType primitiveType,
					   int32_t startVertex,
					   int32_t primitiveCount ) override;

	virtual void Draw( PrimitiveType primitiveType,
					   int32_t indexStart,
					   int32_t indexCount, 
					   int32_t minVertex,
					   int32_t vertexCount ) override;

	const SpD3d9Ex& GetD3d( ) const;
	const SpD3d9DeviceEx& GetD3dDevice( ) const;


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

using GraphicsImpl = D3d9Graphics;
using SpTGraphics = std::shared_ptr<GraphicsImpl>;
using WpTGraphics = std::weak_ptr<GraphicsImpl>;

inline const SpD3d9Ex& D3d9Graphics::GetD3d( ) const
{
	return m_d3d;
}

inline const SpD3d9DeviceEx& D3d9Graphics::GetD3dDevice( ) const
{
	return m_d3dDevice;
}

inline void D3d9Graphics::Clear( )
{
	HRESULT result;
	V( m_d3dDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0, 0, 255 ),
		1.f,
		0 )
	);
}

inline void tgon::D3d9Graphics::Begin( )
{
	HRESULT result;
	V( m_d3dDevice->BeginScene( ));
}

inline void tgon::D3d9Graphics::End( )
{
	HRESULT result;
	V( m_d3dDevice->EndScene( ));
}

inline void tgon::D3d9Graphics::Present( )
{
	HRESULT result;
	V( m_d3dDevice->Present( nullptr, nullptr, nullptr, nullptr ));
}



}