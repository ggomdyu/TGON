/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2015-01-17
*/


#pragma once
#include "IGraphicsDeviceImpl.h"

#include "..\..\include\DirectX\d3d9.h"
#include "..\..\include\DirectX\d3dx9.h"

#include <atlbase.h>
#include <Windows.h>

#include "Direct3D9DeviceMisc.h"
#include "Direct3D9DeviceUtil.h"


//TODO: $(DXSDK_DIR)\Include -> 아예 dxsdk를 통째로 엔진에 집어넣는게 조을듯;

namespace tgon
{




class Direct3D9Device;
typedef Direct3D9Device GraphicsDeviceImpl;

class Direct3D9Device : public IGraphicsDeviceImpl
{
public:
	explicit Direct3D9Device( HWND wndHandle );
	~Direct3D9Device( );

	virtual bool		Setup( const GraphicsDeviceCreateParam* ) override;
	virtual void		Display( ) override;


	//void EndDraw( );


public:
	const CComPtr<IDirect3D9Ex>&				GetD3D( ) const				{ return m_d3d; }
	const CComPtr<IDirect3DDevice9Ex>&		GetD3dDevice( ) const		{ return m_d3dDevice; }


private:
	HRESULT		CreateDevice( D3DDEVTYPE d3dDeviceType, DWORD d3dBehaviorFlag,
							  D3DPRESENT_PARAMETERS& d3dpp );
	void DXErrorHandling( HRESULT hr );


	Direct3D9Device( const Direct3D9Device& ) = delete;
	Direct3D9Device& operator=( const Direct3D9Device& ) = delete;


private:
	CComPtr<IDirect3D9Ex> m_d3d;
	CComPtr<IDirect3DDevice9Ex> m_d3dDevice;

	HWND m_wndHandle;

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