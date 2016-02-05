#include "stdafx.h"
//#include "GraphicsSystem.h"
//
//
//#include "CoreEngine.h"
//#include "D3d9Device.h"
//#include "D3d9Quad.h"
//#include "D3d9Camera.h"
//#include "D3d9Shader.h"
//#include "D3d9Mesh.h"
//
////std::unique_ptr<tgon::D3d9Quad> d3d9Tex;
//
//std::unique_ptr<tgon::D3d9Camera> d3d9Camera;
//std::unique_ptr<tgon::D3d9Shader> d3d9Shader;
//std::unique_ptr<tgon::D3d9Mesh> d3d9Mesh;
//std::unique_ptr<tgon::D3d9Texture> d3d9TextureDiffuse;
//std::unique_ptr<tgon::D3d9Texture> d3d9TextureSpecular;
//
//tgon::GraphicsSystem::GraphicsSystem( ) :
//	ISystem( *this )
//{
//}
//
//
//tgon::GraphicsSystem::~GraphicsSystem( )
//{
//}
//
//void tgon::GraphicsSystem::Setup( )
//{
//	m_gd.reset( new tgGraphicsDevice( *CoreEngine::GetInstance( )->GetWindow( ).get( )));
//
//	// TODO: Use XML and assemble device info!! 
//	tgon::D3dDeviceCreateParam d3dCreateParam;
//	d3dCreateParam.gdpt = tgon::GraphicsDeviceProcessType::kHardware;
//
//	m_gd->Setup( &d3dCreateParam );
//
//
//	//d3d9Shader.reset( new D3d9Shader( m_gd->GetD3dDevice( ), L"Resources\\SpecularMapping.fx" ));
//	//d3d9Mesh.reset( new D3d9Mesh( m_gd->GetD3dDevice( ), L"Resources\\sphere.x" ));
//	//
//	//d3d9TextureDiffuse.reset( new D3d9Texture( m_gd->GetD3dDevice( ), L"Resources\\Fieldstone_DM.tga" ));
//	//d3d9TextureSpecular.reset( new D3d9Texture( m_gd->GetD3dDevice( ), L"Resources\\fieldstone_SM.tga" ));
//
//	//d3d9Camera.reset( new D3d9Camera( m_gd ));
//}
//
////#include "FbxModel.h"
//D3DXVECTOR4 gWorldLightPosition( 500.0f, 500.0f, -500.0f, 1.0f );
//D3DXVECTOR4 gWorldCameraPosition( 0.0f, 0.0f, -200.0f, 1.0f );
//
//void tgon::GraphicsSystem::FrameMove( float elapsedTime )
//{
//	m_gd->BeginDisplay( );
//
//
//	//d3d9Shader->SetMatrix( *d3d9Camera.get( ));
//	//
//	//// Specular light
//	//d3d9Shader->SetVector( "gWorldLightPosition", &gWorldLightPosition );
//	//d3d9Shader->SetVector( "gWorldCameraPosition", &gWorldCameraPosition );
//
//	//// Specular mapping
//	//D3DXVECTOR4 gLightColor( 0.7f, 0.7f, 1.0f, 1.0f );
//	//d3d9Shader->SetVector( "gLightColor", &gLightColor );
//	//d3d9Shader->GetShader( )->SetTexture( "DiffuseMap_Tex", d3d9TextureDiffuse->GetTexture( ));
//	//d3d9Shader->GetShader( )->SetTexture( "SpecularMap_Tex", d3d9TextureSpecular->GetTexture( ));
//
//	//// Texture code
//	////d3d9Shader->GetShader( )->SetTexture( "DiffuseMap_Tex", d3d9Texture->GetTexture( ) );
//
//	//static float f = 0.0f;
//	//f += 0.01f;
//	//
//	//D3DXMATRIX matrix;
//	//D3DXMatrixIdentity( &matrix );
//	//D3DXMatrixRotationX( &matrix, f );
//
//	//m_gd->GetD3dDevice( )->SetTransform( D3DTS_WORLD, &matrix );
//
//
//	//UINT numPasses = 0;
//	//d3d9Shader->GetShader( )->Begin( &numPasses, NULL );
//	//{
//	//	for ( UINT i = 0; i < numPasses; ++i )
//	//	{
//	//		d3d9Shader->GetShader( )->BeginPass( i );
//	//		{
//	//			d3d9Mesh->GetMesh( )->DrawSubset( 0 );
//	//		}
//	//		d3d9Shader->GetShader( )->EndPass( );
//	//	}
//	//}
//	//d3d9Shader->GetShader( )->End( );
//
//	m_gd->EndDisplay( );
//}
//
//
//void tgon::GraphicsSystem::RecvMessage( _In_ const SociableMessage& msg )
//{
//}