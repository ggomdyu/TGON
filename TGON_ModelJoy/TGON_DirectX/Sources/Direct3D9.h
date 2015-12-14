/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/

#pragma once
	#include <atlbase.h>
	#include <Windows.h>
	#include <d3d9.h>
	#include <d3dx9.h>
	#include <atlbase.h>

	#include "Singleton.h"
#ifndef TGON_USE_PRECOMPILED_HEADER
#endif

struct LineVertex
{
	D3DXVECTOR3 pos;
	DWORD color;
};

class GraphicInterfaceLayer
{

};

class Direct3D9 : public Singleton<Direct3D9>
{
public:
	Direct3D9( );
	~Direct3D9( );

	bool Initialize( HWND hWnd );

	void BeginDraw( );
	void EndDraw( );

public:
	CComPtr<IDirect3D9> GetD3d( ) const { return m_d3d; }
	CComPtr<IDirect3DDevice9> GetD3dDevice( ) const { return m_d3dDevice; }


	void DrawLine( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, DWORD color );
	void MoveLocalX( float dist );

private:
	void MakeView( D3DXVECTOR3& eye, D3DXVECTOR3& lookAt, D3DXVECTOR3& up );
	void SetMatrices( );

private:
	CComPtr<IDirect3D9> m_d3d;
	CComPtr<IDirect3DDevice9> m_d3dDevice;

	//D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView, m_matProj;
	D3DXVECTOR3 m_eye, m_lookAt, m_up;
	D3DXVECTOR3 m_vView, m_vCross;
};