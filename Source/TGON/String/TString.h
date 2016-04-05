/*
* 작성자 : 차준호
* 작성일 : 2016-03-27
* 최종 수정 : 
* 최종 수정일 :
*/

#pragma once
#include <string>
#include <stdint.h>


namespace tgon {


	/*
		Encoder
	*/
	// Convert variable-length character to fixed-length
	// cf. https://ko.wikipedia.org/wiki/UTF-8
	void utf8_to_utf16( _In_ const char* const utf8Src,
						_In_ const int32_t length,
						_Out_ wchar_t* const utf16Dest );
	//void utf16_to_utf8( const wchar_t* const utf16Src,
	//					const int32_t length,
	//					_Out_ char* const utf8Dest );

	// wrapped function
	std::wstring utf8_to_utf16( const std::string& utf8Src );
	//std::string utf16_to_utf8( const std::wstring& utf16Src );



	/*
		Shell
	*/
	void GetFileNameFromPath( _Out_ std::wstring* outSrc,
							  bool isDeleteFileExtension );

}