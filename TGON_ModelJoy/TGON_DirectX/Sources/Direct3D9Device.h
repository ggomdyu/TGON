/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2015-01-10
*/


#pragma once
#include <atlbase.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "IGraphicsDeviceImpl.h"


//#pragma comment( lib, "d3d9.lib" )


namespace tgon
{


class Direct3D9Device;
using GraphicsDeviceImpl = Direct3D9Device;



class Direct3D9Device : public IGraphicsDeviceImpl
{
public:
	Direct3D9Device( );
	~Direct3D9Device( );

	virtual bool		Setup( GraphicsDeviceCreateParam gdcp ) override;
	virtual void		Display( ) override;

	/*bool Initialize( HWND hWnd, int width, int height );

	void Display( );
	void EndDraw( );*/


public:
	/*const CComPtr<IDirect3D9>&			GetD3D( ) const				{ return m_d3d; }
	const CComPtr<IDirect3DDevice9>&		GetD3dDevice( ) const		{ return m_d3dDevice; }*/

private:
	Direct3D9Device( const Direct3D9Device& ) = delete;
	Direct3D9Device& operator=( const Direct3D9Device& ) = delete;

private:
	CComPtr<IDirect3D9> m_d3d;
	CComPtr<IDirect3DDevice9> m_d3dDevice;

	HWND m_presentWnd;

	////D3DXMATRIXA16 m_matWorld;
	//D3DXMATRIXA16 m_matView, m_matProj;
	//D3DXVECTOR3 m_eye, m_lookAt, m_up;
	//D3DXVECTOR3 m_vView, m_vCross;
};


//struct ColorVertex
//{
//	enum
//	{
//		FVF = D3DFVF_DIFFUSE | D3DFVF_XYZ,
//	};
//
//	D3DXVECTOR3 pos;
//	DWORD color;
//};
//
//struct TexVertex
//{
//	enum
//	{
//		FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,
//	};
//
//	D3DXVECTOR3 pos;
//	DWORD color;
//	FLOAT u, v;
//};


}