#include "stdafx.h"
#include "D3d9Camera.h"


tgon::D3d9Camera::D3d9Camera( tgGraphicsDevice& gd ) :
	m_d3dDevice( gd.GetD3dDevice( ))
{
	D3DXMatrixIdentity( &m_matWorld );
	D3DXMatrixIdentity( &m_matView );
	D3DXMatrixIdentity( &m_matProj );

	this->SetupMatrix( );
}


tgon::D3d9Camera::~D3d9Camera( )
{
}


void tgon::D3d9Camera::FrameMove( float elapsedTime )
{

}

void tgon::D3d9Camera::SetupMatrix( )
{
	this->SetupWorld( );
	this->SetupView( );
	this->SetupProjection( );
}


void tgon::D3d9Camera::SetupWorld( )
{
	D3DXMatrixIdentity( &m_matWorld );
	m_d3dDevice->SetTransform( D3DTS_WORLD, &m_matWorld );	
}


void tgon::D3d9Camera::SetupView( )
{
	D3DXVECTOR3 vEyePt( 0.0f, 0.0f, -200.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &m_matView, &vEyePt, &vLookatPt, &vUpVec );
	m_d3dDevice->SetTransform( D3DTS_VIEW, &m_matView );
}


void tgon::D3d9Camera::SetupProjection( )
{
	const float aspectRatio = static_cast<float>( GetSystemMetrics( SM_CXSCREEN )) /
								static_cast<float>( GetSystemMetrics( SM_CYSCREEN ));

	D3DXMatrixPerspectiveLH( &m_matProj,
				D3DX_PI /4.0f, // 90 - degree
				aspectRatio,
				1.0f,
				10000.0f );

	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
}