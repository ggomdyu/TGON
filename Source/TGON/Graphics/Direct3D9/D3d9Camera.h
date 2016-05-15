#pragma once
//#include <Graphics/TGraphicsDevice.h>
//#include <memory>
//
//namespace tgon {
//
//
//class D3d9Camera
//{
//public:
//	explicit D3d9Camera( const SpTGraphicsDevice& gd );
//	~D3d9Camera( );
//
//	void FrameMove( float elapsedTime );
//
//public:
//	const D3DXMATRIX& GetWorld( ) const			{ return m_matWorld; }
//	const D3DXMATRIX& GetView( ) const			{ return m_matView; }
//	const D3DXMATRIX& GetProjection( ) const	{ return m_matProj; }
//
//private:
//	void SetupMatrix( );
//	//			...
//	void SetupWorld( );
//	void SetupView( );
//	void SetupProjection( );
//
//	float GetAspectRatio( HWND clientWnd );
//
//private:
//	SpD3d9DeviceEx	m_d3dDevice;
//
//	D3DXMATRIX	m_matWorld;
//	D3DXMATRIX	m_matView;
//	D3DXMATRIX	m_matProj;
//
//	float m_aspectRatio;
//};
//
//
//}