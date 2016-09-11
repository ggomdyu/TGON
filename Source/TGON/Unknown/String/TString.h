/*
* Author : Cha Junho
* Date : 03/27/2016
* Latest author : 
* Latest date :
*/

#pragma once
#include <string>
#include <stdint.h>


namespace tgon {
namespace tgon {
	
// Cf. https://ko.wikipedia.org/wiki/UTF-8
void ConvertUTF_8ToUTF_16( const char* utf8Src, wchar_t* utf16Dest );
	
//
std::wstring ConvertUTF_16ToUTF_8( const std::string& utf8Src );


/*
	Shell
*/
// TODO: Move to TPath
std::wstring GetFileNameFromPath( const wchar_t* srcFileName, bool deleteFileExtension );


// UTF-16
// cf.
/*void UTF16_to_UTF8(
	_In_ const wchar_t* utf16Src,
	const int32_t length,
	_Out_ char* utf8Dest );*/

/*std::wstring UTF16_to_UTF8(
	_In_ const std::wstring& utf16Src );
*/

}