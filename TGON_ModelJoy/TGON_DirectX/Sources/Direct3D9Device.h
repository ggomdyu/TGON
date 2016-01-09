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

#include "GraphicsDevicea.h"

class Direct3D9Device : public GraphicsDevice
{
public:
	Direct3D9Device( );
	~Direct3D9Device( );

	bool Initialize( HWND hWnd, int width, int height );

	void Display( );
	void EndDraw( );

public:
	const CComPtr<IDirect3D9>&				GetD3D( ) const				{ return m_d3d; }
	const CComPtr<IDirect3DDevice9>&		GetD3dDevice( ) const		{ return m_d3dDevice; }

private:
	CComPtr<IDirect3D9> m_d3d;
	CComPtr<IDirect3DDevice9> m_d3dDevice;

	//D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 m_matView, m_matProj;
	D3DXVECTOR3 m_eye, m_lookAt, m_up;
	D3DXVECTOR3 m_vView, m_vCross;
};


struct ColorVertex
{
	enum
	{
		FVF = D3DFVF_DIFFUSE | D3DFVF_XYZ,
	};

	D3DXVECTOR3 pos;
	DWORD color;
};

struct TexVertex
{
	enum
	{
		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
	};

	D3DXVECTOR3 pos;
	DWORD color;
	FLOAT u, v;
};