/*
* 작성자 : 차준호
* 작성일 : 2016-01-20
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "../../Graphics/TGraphics.h"


namespace tgon
{


class D3d9Texture;
using TextureImpl = D3d9Texture;

class D3d9Texture
{
public:
	D3d9Texture( );
	explicit D3d9Texture( const SpTGraphics&, const wchar_t* texPath );
	virtual ~D3d9Texture( );

public:
	void SetTexture( const SpTGraphics&, const wchar_t* texPath );
	const SpD3d9Texture& GetTexture( ) const;

private:
	SpD3d9Texture m_texture;
	static std::map<std::wstring, D3d9Texture*> ms_texPool;
};


inline void D3d9Texture::SetTexture(
	const SpTGraphics& graphics,
	const wchar_t* texPath )
{
	
}

inline const SpD3d9Texture& D3d9Texture::GetTexture( ) const
{
	return m_texture;
}



}