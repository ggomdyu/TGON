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

#include "TWindow.h"
#include "D3d9Type.h"


namespace tgon
{


class D3d9Device;
typedef D3d9Device GraphicsDeviceImpl;


class D3d9Device : public IGraphicsDevice
{
public:
	D3d9Device( const Window::TWindow&, const GraphicsDeviceCreateParam& );
	D3d9Device( const Window::SpTWindow&, const GraphicsDeviceCreateParam& );
	virtual ~D3d9Device( );

	D3d9Device( const D3d9Device& ) = delete;
	D3d9Device& operator=( const D3d9Device& ) = delete;


	virtual void		BeginDisplay( ) override;
	virtual void		EndDisplay( ) override;

public:
	SpD3d9Ex&				GetD3D( )				{ return m_d3d; }
	SpD3d9DeviceEx&		GetD3dDevice( )		{ return m_d3dDevice; }

private:
	bool	Setup( const GraphicsDeviceCreateParam& gdcp );
	void	SetDefRenderState( );

	HRESULT		CreateDevice( D3DDEVTYPE d3dDeviceType, DWORD d3dBehaviorFlag, D3DPRESENT_PARAMETERS& d3dpp );

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