/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/

#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <atlbase.h>
	#include "Singleton.h"
#endif

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE )


class CDirect3D9 : public CSingleton<CDirect3D9>
{
public:
	CDirect3D9( );
	~CDirect3D9( );

	bool Initialize( HWND hWnd );

	void BeginDraw( );
	void EndDraw( );

public:
	CComPtr<IDirect3D9> GetD3D( ) { return m_pd3d9; }
	CComPtr<IDirect3DDevice9> GetD3DDevice( ) { return m_pd3dDevice9; }

	D3DXMATRIXA16* MoveLocalX(float dist);
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);

private:
	void SetMatrices( );

private:
	CComPtr<IDirect3D9> m_pd3d9;
	CComPtr<IDirect3DDevice9> m_pd3dDevice9;

	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProj;
	D3DXVECTOR3 m_vEye, m_vLookAt, m_vUp;

	D3DXVECTOR3		m_vView, m_vCross;
	//D3DXMATRIXA16 m_matWorld, m_matView, m_matProj, m_matOrtho;
};