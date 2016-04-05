/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-20
* ���� ���� :
* ���� ������ :
*/


#pragma once
#include <Graphics/TGraphicsDevice.h>
#include "D3d9Type.h"

namespace tgon {


class D3d9Texture;
typedef D3d9Texture TextureImpl;


class D3d9Texture
{
public:
	D3d9Texture( );
	explicit D3d9Texture( const SpTGraphicsDevice& gd, const wchar_t* texturePath );
	~D3d9Texture( );

	void SetTexture( const SpTGraphicsDevice& gd, const wchar_t* texturePath );

public:
	const SpD3d9Texture& GetTexture( ) const { return m_texture; }

private:
	SpD3d9Texture m_texture;

};


}