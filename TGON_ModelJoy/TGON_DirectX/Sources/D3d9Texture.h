/*
* 작성자 : 차준호
* 작성일 : 2016-01-20
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include "D3d9Type.h"

namespace tgon {


class D3d9Texture;
typedef D3d9Texture TextureImpl;


class D3d9Texture
{
public:
	D3d9Texture( );
	D3d9Texture( SpD3d9DeviceEx& gd, const wchar_t* texturePath );
	~D3d9Texture( );

public:
	void SetTexture( SpD3d9DeviceEx& gd, const wchar_t* texturePath );


public:
	const SpD3d9Texture&	GetTexture( ) const		{ return m_texture; }

private:
	SpD3d9Texture m_texture;

};


}