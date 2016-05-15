#include "PrecompiledHeader.h"
#include "D3d9Quad.h"
//
//
//tgon::D3d9Quad::D3d9Quad( SpTGraphicsDevice& gd, const wchar_t* filePath ) :
//	//IQuad( gd ),
//	m_d3dShader( gd, filePath )
//{
//	assert( gd.get());
//
//	if ( filePath )
//	{
//		this->MakeQuad( );
//	}
//}
//
//
//tgon::D3d9Quad::~D3d9Quad( )
//{
//}
//
//
//struct Vertex
//{
//	float x, y, z;			// XYZ
//	float nx, ny, nz;		// Normal
//	float u, v;			// Tex
//};
//
////const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
//void tgon::D3d9Quad::Draw( )
//{
//	/*this->GetD3dDevice( )->SetTexture( 0, m_d3dTexture.GetTexture( ) );
//
//	this->GetD3dDevice( )->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
//	this->GetD3dDevice( )->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
//	this->GetD3dDevice( )->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
//
//	this->GetD3dDevice( )->SetRenderState( D3DRS_LIGHTING, false );
//
//	this->GetD3dDevice( )->SetStreamSource( 0, m_quadVB, 0, sizeof( Vertex ) );
//	this->GetD3dDevice( )->SetFVF( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 );
//	this->GetD3dDevice( )->DrawPrimitive( D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, 2 );*/
//
//}
//
//
//void tgon::D3d9Quad::MakeQuad( )
//{
//	//dxerr::DXErrorException( GetGraphicsDevice( ).GetD3dDevice( )->CreateVertexBuffer(
//	//		4*sizeof( Vertex ),
//	//		D3DUSAGE_WRITEONLY,
//	//		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
//	//		D3DPOOL::D3DPOOL_DEFAULT,
//	//		&m_quadVB,
//	//		NULL
//	//));
//	//assert( m_quadVB.p );
//
//
//	//Vertex* v = nullptr;
//	//dxerr::DXErrorException( m_quadVB->Lock( 0, 0, reinterpret_cast<void**>( &v ), 0 ));
//
//	//v[0] = { -1.0f, -1.0f, 1.25f,	0.0f, 0.0f, -1.0f,		0.0f, 1.0f };
//	//v[1] = { -1.0f, 1.0f, 1.25f,		0.0f, 0.0f, -1.0f,		0.0f, 0.0f };
//	//v[2] = { 1.0f, 1.0f, 1.25f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f };
//	//v[3] = { -1.0f, -1.0f, 1.25f,	0.0f, 0.0f, -1.0f,		0.0f, 1.0f };
//	//v[4] = { 1.0f, 1.0f, 1.25f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f };
//	//v[5] = { 1.0f, -1.0f, 1.25f,		0.0f, 0.0f, -1.0f,		1.0f, 1.0f };
//
//	//dxerr::DXErrorException(	m_quadVB->Unlock( ));
//
//	//assert( v );
//}
////
////
