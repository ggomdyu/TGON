#pragma once





inline const SpD3d9DeviceEx& D3d9Graphics::GetD3dDevice( ) const
{
	return m_d3dDevice;
}

inline void D3d9Graphics::Clear( )
{
	HRESULT result;
	V( m_d3dDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB( 0, 0, 255 ),
		1.f,
		0 )
	);
}

inline void tgon::D3d9Graphics::Begin( )
{
	HRESULT result;
	V( m_d3dDevice->BeginScene( ));
}

inline void tgon::D3d9Graphics::End( )
{
	HRESULT result;
	V( m_d3dDevice->EndScene( ));
}

inline void tgon::D3d9Graphics::Present( )
{
	HRESULT result;
	V( m_d3dDevice->Present( nullptr, nullptr, nullptr, nullptr ));
}