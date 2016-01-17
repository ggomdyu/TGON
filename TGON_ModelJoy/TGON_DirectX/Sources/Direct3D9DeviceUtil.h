#pragma once
#include <string>



namespace tgon
{


typedef std::wstring DxErrString;
void GetDXErrorString( HRESULT hr, _Out_ DxErrString* desc );


}