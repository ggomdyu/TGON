/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 김태우
* 최종 수정일 : 2015-04-26
*/


#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "Singleton.h"
#include "Define.h"

#pragma comment( lib, "d3d9.lib" )
#ifdef _DEBUG
	#pragma comment( lib, "d3dx9d.lib" )
#else
	#pragma comment( lib, "d3dx9.lib" )
#endif

#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )



class CDirect3D : public CSingleton<CDirect3D>
{
private:
	LPDIRECT3D9			m_pD3D9;
	LPDIRECT3DDEVICE9	m_pD3DDevice9;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	std::vector<CUSTOMVERTEX*> m_Vertexs;

public:
	CDirect3D( void );
	~CDirect3D( void );

	HRESULT	Initialize( HWND hWnd, bool isWindow );
	HRESULT InitializeVB( );
	void SetMatrices( );
	void Render( );
	void Release( );

public:
	inline LPDIRECT3D9 GetD3D( ) { return m_pD3D9; }
	inline LPDIRECT3DDEVICE9 GetD3DDevice( ) { return m_pD3DDevice9; }
	inline LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer( ) { return m_pVB; }
	inline std::vector<CUSTOMVERTEX*>* GetVertexVector( ) { return &m_Vertexs; }
};
#define Direct3D() CSingleton<CDirect3D>::InstancePtr()
