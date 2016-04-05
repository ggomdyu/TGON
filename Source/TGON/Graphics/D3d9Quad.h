/*
* 작성자 : 차준호
* 작성일 : 2016-01-20
* 최종 수정 :
* 최종 수정일 : 
*/


#pragma once
//#include "IQuad.h"
#include "Graphics/TGraphicsDevice.h"
#include "D3d9Type.h"
#include "D3d9Shader.h"


namespace tgon {


class D3d9Quad;
typedef D3d9Quad QuadImpl;


class D3d9Quad //: public IQuad
{
public:
	explicit	D3d9Quad( SpTGraphicsDevice& gd, const wchar_t* filePath = nullptr );
	virtual		~D3d9Quad( );

	virtual void	Draw( );// override;

private:
	SpD3d9DeviceEx&		GetD3dDevice( )	 { return GetD3dDevice( ); }
	void						MakeQuad( );

private:
	D3d9Shader			m_d3dShader;
	SpVertexBuffer		m_quadVB;
};


}