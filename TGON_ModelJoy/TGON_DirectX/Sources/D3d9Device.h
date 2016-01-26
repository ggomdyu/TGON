/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-17
*/


#pragma once
#include "IGraphicsDevice.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <atlbase.h>
#include <Windows.h>

#include "tgWindow.h"
#include "D3d9Type.h"
#include "D3d9Util.h"


namespace tgon
{

class D3d9Device;
typedef D3d9Device GraphicsDeviceImpl;


struct D3dDeviceCreateParam : public GraphicsDeviceCreateParam
{
	virtual ~D3dDeviceCreateParam( ) {}

	bool isFullWindow;
	GraphicsDeviceProcessType gdpt;
};


class D3d9Device : public IGraphicsDevice
{
public:
	explicit D3d9Device( const tgWindow& tgWnd );
	~D3d9Device( );

	virtual bool		Setup( const GraphicsDeviceCreateParam* ) override;

	virtual void		BeginDisplay( ) override;
	virtual void		EndDisplay( ) override;

public:
	SpD3d9Ex&				GetD3D( )				{ return m_d3d; }
	SpD3d9DeviceEx&		GetD3dDevice( )		{ return m_d3dDevice; }

private:
	D3d9Device( const D3d9Device& ) = delete;
	D3d9Device& operator=( const D3d9Device& ) = delete;

	HRESULT		CreateDevice( D3DDEVTYPE d3dDeviceType, DWORD d3dBehaviorFlag,
							D3DPRESENT_PARAMETERS& d3dpp );
	//void			

private:
	SpD3d9Ex			m_d3d;
	SpD3d9DeviceEx	m_d3dDevice;

	const HWND		m_wndHandle;

	////D3DXMATRIXA16 m_matWorld;
	//D3DXMATRIXA16 m_matView, m_matProj;
	//D3DXVECTOR3 m_eye, m_lookAt, m_up;
	//D3DXVECTOR3 m_vView, m_vCross;
};


}