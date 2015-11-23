#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-16
* 최종 수정 : 
* 최종 수정일 : 
*/

#include "BaseModel.h"
#include "Direct3D9.h"

class WindowsFBXBase : public BaseModel
{
public:
	WindowsFBXBase()
	{
		D3DXMatrixIdentity( &m_matLocal );
	};
	~WindowsFBXBase() {};

	virtual void Render( ) override
	{
		CDirect3D9::get( )->GetD3DDevice( )->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ));
		CDirect3D9::get( )->GetD3DDevice( )->SetFVF( D3DFVF_CUSTOMVERTEX );
		CDirect3D9::get( )->GetD3DDevice( )->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_pFbxMesh->GetPolygonCount( ));
	}

private:
	D3DXMATRIX m_matLocal;

	CComPtr<IDirect3DVertexBuffer9> m_pVB;
	std::vector<CUSTOMVERTEX> m_vertices;
};