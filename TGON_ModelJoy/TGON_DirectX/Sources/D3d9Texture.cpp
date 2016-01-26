#include "stdafx.h"
#include "D3d9Texture.h"

#include "D3d9Util.h"


tgon::D3d9Texture::D3d9Texture( ) 
{
}


tgon::D3d9Texture::D3d9Texture( SpD3d9DeviceEx& gd, const wchar_t* texturePath ) :
	m_texture( dxgraphics::LoadTexture( gd, texturePath ))
{
}


tgon::D3d9Texture::~D3d9Texture( )
{
}


void tgon::D3d9Texture::SetTexture( SpD3d9DeviceEx& gd, const wchar_t* texturePath )
{
	m_texture = std::move( dxgraphics::LoadTexture( gd, texturePath ));
}