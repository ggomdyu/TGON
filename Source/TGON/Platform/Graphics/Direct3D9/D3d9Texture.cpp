#include "PrecompiledHeader.h"
#include "D3d9Texture.h"


//tgon::D3d9Texture::D3d9Texture( const SpTGraphicsDevice& gd, const wchar_t* texturePath ) :
//	m_texture( LoadTexture( gd->GetD3dDevice(), texturePath ))
//{
//	assert( gd.get());
//	assert( texturePath );
//}
//void tgon::D3d9Texture::SetTexture( const SpTGraphicsDevice& gd, const wchar_t* texturePath )
//{
//	assert( gd.get());
//	assert( texturePath );
//
//	
//}

decltype ( tgon::D3d9Texture::ms_texturePool ) tgon::D3d9Texture::ms_texturePool;

tgon::D3d9Texture::D3d9Texture(
	const SpTGraphics& grp,
	const wchar_t* texturePath )
{
	D3DXCreateTexture( );
}

tgon::D3d9Texture::~D3d9Texture( )
{
}

void tgon::D3d9Texture::SetTexture( const SpTGraphics &, const wchar_t * texturePath )
{
}

SpD3D9Texture tgon::D3d9Texture::GetTexture( ) const
{
	return SpD3D9Texture( );
}

void tgon::D3d9Texture::LoadTexture( 
	const SpTGraphics&, 
	const wchar_t* texurePath )
{
	const auto findIter = ms_texPool.find( texPath );
	if ( findIter == ms_texPool.end( ))
	{
		IDirect3DTexture9* texture = nullptr;
		HRESULT hr = D3DXCreateTextureFromFileW( 
			grp->GetD3dDevice( ),
			texPath,
			&texture
		);

		if ( FAILED( hr ))
		{
			MessageBox( 
				GetFocus( ),
				L"Failed to invoke D3DXCreateTextureFromFileW.",
				L"WARNING!",
				MB_OK | MB_ICONEXCLAMATION 
			);
		}
	}
}