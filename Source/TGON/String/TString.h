/*
* Author : Junho-Cha
* Date : 03/27/2016
* Latest author : 
* Latest date :
*/

#pragma once
#include <string>
#include <stdint.h>


namespace tgon
{
	/*
		Convert encoding
	*/
	// UTF-8
	// cf. https://ko.wikipedia.org/wiki/UTF-8
	
	void UTF8_to_UTF16( 
		_In_ const char* utf8Src, 
		_Out_ wchar_t* utf16Dest );
	
	std::wstring UTF8_to_UTF16( 
		_In_ const std::string& utf8Src );


	/*
		Shell
	*/
	void GetFileNameFromPath(
		std::wstring* dest,
		bool deleteFileExtension );


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