#include "stdafx.h"
#include "D3d9Mesh.h"

#include "D3d9Util.h"

tgon::D3d9Mesh::D3d9Mesh( SpD3d9DeviceEx& device, const wchar_t* meshPath ) :
	m_mesh( dxgraphics::LoadMesh( device, meshPath ))
{
}


tgon::D3d9Mesh::~D3d9Mesh( )
{
	
}
