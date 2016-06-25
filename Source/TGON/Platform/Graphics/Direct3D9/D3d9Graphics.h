/*
* Author : Taewoo-Kim
* Date : 04/26/2015
* Latest author : Junho-Cha
* Latest date : 01/17/2016
*/


#pragma once
#include "../../Config/Build.h"
#include "../Abstract/AbstractGraphics.h"
#include "../GraphicsStyle.h"
#include "../../Window/TWindow.h"

#include <d3d9.h>
#include "D3d9Util.h"
#include "../../../Platform/Utility/Windows/shared_comptr.h"

#pragma comment( lib, "d3d9.lib" )
#if defined( _DEBUG ) || defined( DEBUG )
#	pragma comment( lib, "d3dx9d.lib" )
#else
#	pragma comment( lib, "d3dx9.lib" )
#endif


namespace tgon
{


using GraphicsImpl = class D3D9Graphics;
using SpTGraphics = std::shared_ptr<GraphicsImpl>;
using WpTGraphics = std::weak_ptr<GraphicsImpl>;

using SpD3D9Ex = tgon::shared_comptr<struct IDirect3D9Ex>;
using SpD3D9DeviceEx = tgon::shared_comptr<struct IDirect3DDevice9Ex>;


class TGON_API D3D9Graphics : 
	private AbstractGraphics
{
public:
	static SpTGraphics Make( 
		const TWindow& window,
		const GraphicsStyle& grpStyle = GraphicsStyle( ))
	{
		SpTGraphics grp( new D3D9Graphics( window, grpStyle ));
		return grp;
	}

	virtual ~D3D9Graphics( );

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

public:
	const SpD3D9DeviceEx& GetD3dDevice( ) const;
	const SpD3D9Ex& GetD3d( ) const;

private:
	explicit D3D9Graphics( const TWindow&,
						   const GraphicsStyle& );

private:
	void InitD3D( );
	void InitD3DDevice( const TWindow&,
						const GraphicsStyle& grpStyle );

private:
	SpD3D9DeviceEx m_d3dDevice;
	SpD3D9Ex m_d3d;
	D3DCAPS9 m_d3dCaps;
};

inline const SpD3D9Ex& D3D9Graphics::GetD3d( ) const
{
	return nullptr;
}

inline const SpD3D9DeviceEx& D3D9Graphics::GetD3dDevice( ) const
{
	return nullptr;
}

inline void D3D9Graphics::Clear( )
{
	HRESULT hr;
	V( m_d3dDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 41, 79, 121 ),
		1.f,
		0 )
	);
}

inline void tgon::D3D9Graphics::Begin( )
{
	HRESULT hr;
	V( m_d3dDevice->BeginScene( ));
}

inline void tgon::D3D9Graphics::End( )
{
	HRESULT hr;
	V( m_d3dDevice->EndScene( ));
}

inline void tgon::D3D9Graphics::Present( )
{
	HRESULT hr ;
	V( m_d3dDevice->Present( nullptr, nullptr, nullptr, nullptr ));
}


}