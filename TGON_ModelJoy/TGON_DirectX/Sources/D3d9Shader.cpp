#include "stdafx.h"
#include "D3d9Shader.h"


tgon::D3d9Shader::D3d9Shader( SpD3d9DeviceEx& device, const wchar_t* shaderPath ) :
	m_shader( dxgraphics::LoadShader( device, shaderPath ))
{
}


tgon::D3d9Shader::D3d9Shader( SpD3d9DeviceEx& device, const wchar_t* shaderPath, const wchar_t* texturePath ) :
	m_shader( dxgraphics::LoadShader( device, shaderPath )),
	m_texture( device, texturePath )
{
}

void tgon::D3d9Shader::SetTexture( const D3d9Texture& texture )
{
}


tgon::D3d9Shader::~D3d9Shader( )
{
}


void tgon::D3d9Shader::BeginDisplay( )
{
	//unsigned int numPasses = 0;
	//GetShader( )->Begin( &numPasses, NULL );

	//for ( unsigned int i = 0; i < numPasses; ++i )
	//{
	//	GetShader( )->BeginPass( i );
	//}

}


void tgon::D3d9Shader::EndDisplay( )
{
	//GetShader( )->EndPass( );
//	GetShader( )->End( );
}




void tgon::D3d9Shader::SetMatrix( const D3d9Camera& camera )
{
	DxErrorException( GetShader( )->SetMatrix( "gWorldMatrix", &camera.GetWorld( )));
	DxErrorException( GetShader( )->SetMatrix( "gViewMatrix", &camera.GetView( )));
	DxErrorException( GetShader( )->SetMatrix( "gProjectionMatrix", &camera.GetProjection( )));
}