#include "stdafx.h"
#include "D3d92DSprite.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "D3d9Util.h"


tgon::D3d92DSprite::D3d92DSprite( const SpTGraphicsDevice& gd,
								  const wchar_t* spritePath ) :
	m_gd( gd )
{
	HRESULT result;
	
	V( D3DXCreateTextureFromFileExW(
			gd->GetD3dDevice( ),
			spritePath,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0xffff00ff,
			&m_imgInfo,
			NULL,
			&m_texture
		));
}


tgon::D3d92DSprite::~D3d92DSprite( )
{
}


void tgon::D3d92DSprite::SetMatrix( )
{
}

void tgon::D3d92DSprite::Render( )
{
	HRESULT result;
	const RECT drawArea{ 0, 0, GetWidth( ), GetHeight( ) };
	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity( &matWorld );
	D3DXMatrixTranslation( &matWorld, 100.0f, 0.0f, 0.0f );

	// Pls change to DOD

	V( SUCCEEDED( m_gd->GetD3dSprite()->Begin( D3DXSPRITE_ALPHABLEND )));
	{
		m_gd->GetD3dDevice( )->SetTransform( D3DTS_WORLD, &matWorld );
		m_gd->GetD3dSprite( )->Draw( m_texture, &drawArea, NULL, NULL, 0xffffffff );
		m_gd->GetD3dSprite( )->End( );
	}
	V( SUCCEEDED( m_gd->GetD3dSprite()->End()));
}

uint32_t tgon::D3d92DSprite::GetWidth( )
{
	return m_imgInfo.Width;
}

uint32_t tgon::D3d92DSprite::GetHeight( )
{
	return m_imgInfo.Height;
}
