#include "stdafx.h"
#include "GraphicsSystem.h"


#include "WindowSystem.h"
#include "D3d9Device.h"
#include "D3d9Quad.h"
#include "D3d9Camera.h"
#include "D3d9Shader.h"
#include "D3d9Mesh.h"

//std::unique_ptr<tgon::D3d9Quad> d3d9Tex;

std::unique_ptr<tgon::D3d9Camera> d3d9Camera;
std::unique_ptr<tgon::D3d9Shader> d3d9Shader;
std::unique_ptr<tgon::D3d9Mesh> d3d9Mesh;
std::unique_ptr<tgon::D3d9Texture> d3d9Texture;

tgon::GraphicsSystem::GraphicsSystem( ) :
	ISystem( *this ),
	gd( GetWindowSystem( )->GetWindow( ))
{
	// TODO: Use XML and assemble device info!! 
	tgon::D3dDeviceCreateParam d3dCreateParam;
	d3dCreateParam.gdpt = tgon::GraphicsDeviceProcessType::kHardware;

	gd.Setup( &d3dCreateParam );


	d3d9Shader.reset( new D3d9Shader( gd.GetD3dDevice( ), L"Resources\\TextureMapping.fx" ));
	d3d9Mesh.reset( new D3d9Mesh( gd.GetD3dDevice( ), L"Resources\\sphere.x" ));
	d3d9Texture.reset( new D3d9Texture( gd.GetD3dDevice( ), L"Resources\\Earth.jpg" ));


	d3d9Camera.reset( new D3d9Camera( gd ));
}


tgon::GraphicsSystem::~GraphicsSystem( )
{
}


void tgon::GraphicsSystem::Initialize( )
{
}


void tgon::GraphicsSystem::FrameMove( float elapsedTime )
{
	gd.BeginDisplay( );

	d3d9Shader->SetMatrix( *d3d9Camera.get( ) );
	d3d9Shader->GetShader( )->SetTexture( "DiffuseMap_Tex", d3d9Texture->GetTexture( ) );

	UINT numPasses = 0;
	d3d9Shader->GetShader( )->Begin( &numPasses, NULL );
	{
		for ( UINT i = 0; i < numPasses; ++i )
		{
			d3d9Shader->GetShader( )->BeginPass( i );
			{
				d3d9Mesh->GetMesh( )->DrawSubset( 0 );
			}
			d3d9Shader->GetShader( )->EndPass( );
		}
	}
	d3d9Shader->GetShader( )->End( );

	gd.EndDisplay( );
}


void tgon::GraphicsSystem::RecvMessage( _In_ const SociableMessage& msg )
{
}