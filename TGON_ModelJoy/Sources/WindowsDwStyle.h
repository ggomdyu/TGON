#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <iostream>
#endif

typedef unsigned long DWORD;
struct WindowStyle;

struct CDwStyle
{
	CDwStyle( const DWORD _dwStyle = 0 ) :
		dwStyle( _dwStyle ) {}

	operator DWORD&( ) { return dwStyle; }

private:
	DWORD dwStyle;
};

struct CDwExStyle
{
	CDwExStyle( const DWORD _dwExStyle = 0 ) :
		dwExStyle( _dwExStyle ) {}

	operator DWORD&( ) { return dwExStyle; }

private:
	DWORD dwExStyle;
};

//	Convert 'WindowStyle' structure to CDwExStyle or CDwStyle.
void ConvertWsToDw( _In_ const WindowStyle&, _Out_ CDwExStyle* const, _Out_ CDwStyle* const );