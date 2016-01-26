#pragma once
#include "D3d9Type.h"

namespace tgon {


class D3d9Mesh
{
public:
	explicit D3d9Mesh( SpD3d9DeviceEx& device, const wchar_t* meshPath );
	~D3d9Mesh( );

	const SpD3d9Mesh& GetMesh( ) { return m_mesh; }

private:
	SpD3d9Mesh	m_mesh;
};



}