/*
* 작성자 : 차준호
* 작성일 : 2016-01-20
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include "D3D9Graphics.h"
#include "../Platform/Misc/Windows/shared_comptr.h"


namespace tgon
{


using TextureImpl = class D3d9Texture;
using SpTTexture = std::shared_ptr<TextureImpl>;
using WpTTexture = std::weak_ptr<TextureImpl>;

using SpD3D9Texture = tgon::shared_comptr<struct IDirect3DTexture9>;


class D3d9Texture
{
public:
	explicit D3d9Texture( const SpTGraphics& );
	virtual ~D3d9Texture( );

public:
	void SetTexture( const SpTGraphics& );
	SpD3D9Texture GetTexture( ) const;

private:
	void LoadTexture( const SpTGraphics& );

private:
	SpD3D9Texture m_texture;
	static std::map<std::wstring, SpD3D9Texture> ms_texturePool;
};


}