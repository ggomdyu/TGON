/*
* Author : Junho-Cha
* Date : 2016-03-23
* Latest author :
* Latest date :
*/

#pragma once
#include <string>
#include <iostream>
#include <stdint.h>


namespace tgon
{


class LayeredConsole
{
protected:
	LayeredConsole( ) : m_isFlashOnLogging( false ) {};
	virtual ~LayeredConsole( ) = 0 {};

public:
	virtual void WriteLine( ) = 0;

	void SetFlashOnLogging( bool isFlashOnLogging );
	bool IsFlashOnLogging( ) const;

protected:
	template<class T>
	void FillBuffer( const T& arg );
	void FillBuffer( const wchar_t* arg );
	void FillBuffer( const char* arg );

	void ClearBuffer( );
	const std::wstring& GetBuffer( ) const;

private:
	std::wstring m_buf;
	bool m_isFlashOnLogging;
};


}


#include "LayeredConsole.hpp"