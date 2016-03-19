#include "stdafx.h"
#include "D3d9Texture.h"

#include "D3d9Util.h"


tgon::D3d9Texture::D3d9Texture( ) 
{
}


tgon::D3d9Texture::D3d9Texture( const SpTGraphicsDevice& gd, const wchar_t* texturePath ) :
	m_texture( LoadTexture( gd->GetD3dDevice(), texturePath ))
{
	assert( gd.get());
	assert( texturePath );
}

void tgon::D3d9Texture::SetTexture( const SpTGraphicsDevice& gd, const wchar_t* texturePath )
{
	assert( gd.get());
	assert( texturePath );

	m_texture = LoadTexture( gd->GetD3dDevice(), texturePath );
}

tgon::D3d9Texture::~D3d9Texture( )
{
}

