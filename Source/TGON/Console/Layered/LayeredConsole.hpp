#pragma once
#include "LayeredConsole.h"
#include "../../Config/Compiler/SyntaxCompatible.hpp"


template<class T>
TGON_FORCEINLINE void tgon::LayeredConsole::FillBuffer( const T& arg ) 
{
	m_buf += std::to_wstring( arg );
};


TGON_FORCEINLINE void tgon::LayeredConsole::SetFlashOnLogging( bool isFlashOnLogging )
{
	m_isFlashOnLogging = isFlashOnLogging;
}


TGON_FORCEINLINE void tgon::LayeredConsole::FillBuffer( const wchar_t* arg )
{
	m_buf += arg;
}


TGON_FORCEINLINE const std::wstring& tgon::LayeredConsole::GetBuffer( ) const 
{
	return m_buf;
}


TGON_FORCEINLINE bool tgon::LayeredConsole::IsFlashOnLogging( ) const
{
	return m_isFlashOnLogging;
}


TGON_FORCEINLINE void tgon::LayeredConsole::ClearBuffer( )
{
	m_buf.clear( );
}