#pragma once
#include "LayeredConsole.h"
#include "../../Config/Compiler/SyntaxCompatible.hpp"


template<class T>
inline void tgon::LayeredConsole::FillBuffer( const T& arg ) 
{
	m_buf += std::to_wstring( arg );
};

inline void tgon::LayeredConsole::SetFlashOnLogging( bool isFlashOnLogging )
{
	m_isFlashOnLogging = isFlashOnLogging;
}

inline void tgon::LayeredConsole::FillBuffer( const wchar_t* arg )
{
	m_buf += arg;
}

inline const std::wstring& tgon::LayeredConsole::GetBuffer( ) const 
{
	return m_buf;
}

inline bool tgon::LayeredConsole::IsFlashOnLogging( ) const
{
	return m_isFlashOnLogging;
}

inline void tgon::LayeredConsole::ClearBuffer( )
{
	m_buf.clear( );
}