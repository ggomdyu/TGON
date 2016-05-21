/*
* Author : Junho-Cha
* Date : 05/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Platform/Config/BuildOption.h"
#include "WindowsMessageBoxType.h"


namespace tgon
{


using MsgBoxResultImpl = WindowsMsgBoxResult;
using MsgBoxButtonImpl = WindowsMsgBoxButton;
using MsgBoxFlagImpl = WindowsMsgBoxFlag;
using MessageBoxImpl = class WindowsMessageBox;


class TGON_API WindowsMessageBox
{
public:
	static WindowsMsgBoxResult Show( const wchar_t* text, const wchar_t* caption, WindowsMsgBoxButton msgBoxButton, WindowsMsgBoxFlag msgBoxFlag );
};


inline WindowsMsgBoxResult WindowsMessageBox::Show( 
	const wchar_t* text,
	const wchar_t* caption,
	WindowsMsgBoxButton msgBoxButton, 
	WindowsMsgBoxFlag msgBoxFlag )
{
	auto ret = MessageBoxW(
		GetFocus( ),
		text,
		caption,
		static_cast<UINT>( msgBoxButton ) | static_cast<UINT>( msgBoxFlag )
	);

	return static_cast<WindowsMsgBoxResult>( ret );
}


}