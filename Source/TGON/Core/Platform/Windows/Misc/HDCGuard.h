#pragma once
#include <Windows.h>

class HDCGuard
{
public:
	HDCGuard( const HWND wndHandle, const HDC dcHandle ) :
		m_dcHandle( dcHandle ),
		m_wndHandle( wndHandle )
	{
	}
	~HDCGuard( )
	{
		ReleaseDC( m_wndHandle, m_dcHandle );
	}

	operator HDC( ) const;
	operator HDC*( );
	operator HDC&( );

private:
	const HWND m_wndHandle;
	HDC m_dcHandle;
};

inline HDCGuard::operator HDC( ) const
{
	return m_dcHandle;
}

inline HDCGuard::operator HDC*( )
{
	return &m_dcHandle;
}

inline HDCGuard::operator HDC&( )
{
	return m_dcHandle;
}