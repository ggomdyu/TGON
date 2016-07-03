/*
* Author : Junho-Cha
* Date : 05/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "TMessageBoxType.h"


namespace tgon
{


using TMsgBoxResult = WindowsMsgBoxResult;

class TGON_API TMessageBox : public MessageBoxImpl
{
public:
	static TMsgBoxResult Show( const wchar_t* text );
	static TMsgBoxResult Show( const wchar_t* text, TMsgBoxButton msgBoxButton );
	static TMsgBoxResult Show( const wchar_t* text, TMsgBoxFlag msgBoxFlag );
	static TMsgBoxResult Show( const wchar_t* text, const wchar_t* caption, TMsgBoxButton msgBoxButton );
	static TMsgBoxResult Show( const wchar_t* text, const wchar_t* caption, TMsgBoxFlag msgBoxButton );
	static TMsgBoxResult Show( const wchar_t* text, const wchar_t* caption, TMsgBoxButton msgBoxButton, TMsgBoxFlag msgBoxFlag );

	static TMsgBoxResult Show( const char* text );
	static TMsgBoxResult Show( const char* text, TMsgBoxButton msgBoxButton );
	static TMsgBoxResult Show( const char* text, TMsgBoxFlag msgBoxFlag );
	static TMsgBoxResult Show( const char* text, const char* caption, TMsgBoxButton msgBoxButton );
	static TMsgBoxResult Show( const char* text, const char* caption, TMsgBoxFlag msgBoxButton );
	static TMsgBoxResult Show( const char* text, const char* caption, TMsgBoxButton msgBoxButton, TMsgBoxFlag msgBoxFlag );
};


// wchar_t

inline TMsgBoxResult TMessageBox::Show( 
	const wchar_t* text )
{
	return MessageBoxImpl::Show( 
		text,
		L"",
		MsgBoxButtonImpl::Ok,
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const wchar_t* text, 
	TMsgBoxButton msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		L"",
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const wchar_t* text, 
	TMsgBoxFlag msgBoxFlag )
{
	return MessageBoxImpl::Show( 
		text,
		L"",
		MsgBoxButtonImpl::Ok,
		static_cast<MsgBoxFlagImpl>( msgBoxFlag )
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const wchar_t* text, 
	const wchar_t* caption, 
	TMsgBoxButton msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		caption,
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const wchar_t* text, 
	const wchar_t* caption,
	TMsgBoxFlag msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		caption,
		MsgBoxButtonImpl::Ok,
		static_cast<MsgBoxFlagImpl>( msgBoxButton )
	);
}

inline TMsgBoxResult TMessageBox::Show(
	const wchar_t* text,
	const wchar_t* caption,
	TMsgBoxButton msgBoxButton, 
	TMsgBoxFlag msgBoxFlag )
{
	return MessageBoxImpl::Show( 
		text,
		L"",
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		static_cast<MsgBoxFlagImpl>( msgBoxFlag )
	);
}

// char

inline TMsgBoxResult TMessageBox::Show( 
	const char* text )
{
	return MessageBoxImpl::Show( 
		text,
		"",
		MsgBoxButtonImpl::Ok,
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const char* text, 
	TMsgBoxButton msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		"",
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const char* text, 
	TMsgBoxFlag msgBoxFlag )
{
	return MessageBoxImpl::Show( 
		text,
		"",
		MsgBoxButtonImpl::Ok,
		static_cast<MsgBoxFlagImpl>( msgBoxFlag )
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const char* text, 
	const char* caption, 
	TMsgBoxButton msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		caption,
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		MsgBoxFlagImpl::None
	);
}

inline TMsgBoxResult TMessageBox::Show( 
	const char* text, 
	const char* caption,
	TMsgBoxFlag msgBoxButton )
{
	return MessageBoxImpl::Show( 
		text,
		caption,
		MsgBoxButtonImpl::Ok,
		static_cast<MsgBoxFlagImpl>( msgBoxButton )
	);
}

inline TMsgBoxResult TMessageBox::Show(
	const char* text,
	const char* caption,
	TMsgBoxButton msgBoxButton, 
	TMsgBoxFlag msgBoxFlag )
{
	return MessageBoxImpl::Show( 
		text,
		"",
		static_cast<MsgBoxButtonImpl>( msgBoxButton ),
		static_cast<MsgBoxFlagImpl>( msgBoxFlag )
	);
}

}