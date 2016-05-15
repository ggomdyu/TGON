#include "PrecompiledHeader.h"
#include "TString.h"
	
#include <cassert>


void tgon::UTF8_to_UTF16(
	const char* utf16Src, 
	wchar_t* utf16Dest )
{
	enum BinaryTable
	{
		_1000_0000 = 0x80,
		_1100_0000 = 0xC0,
		_1110_0000 = 0xE0,
		_0001_1111 = 0x1F,
		_0011_1111 = 0x3F,
	};

	int32_t destIndex = 0;
	for ( int32_t i = 0; utf16Src[i] != '\0'; ++i )
	{
		// 000000-00007F : America
		if (( utf16Src[i] & _1000_0000 ) == 0 )
		{
			utf16Dest[destIndex++] = utf16Src[i];
		}

		// 000080-0007FF : Europe
		else if (( utf16Src[i] & _1110_0000 ) == _1100_0000 &&
				 ( utf16Src[i+1] & _1100_0000 ) == _1000_0000 )
		{
			const wchar_t ch =
				(( utf16Src[i] & _0001_1111 ) << 6 ) +
				( utf16Src[i] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 1;
		}
		// 000800-00FFFF : Asia
		else if (( utf16Src[i] & _1110_0000 ) == _1110_0000 &&
				 ( utf16Src[i+1] & _1100_0000 ) == _1000_0000 &&
				 ( utf16Src[i+2] & _1100_0000 ) == _1000_0000 )
		{
			const wchar_t ch = 
				( utf16Src[i] << 12 ) +
				(( utf16Src[i+1] & _0011_1111 ) << 6 ) +
				( utf16Src[i+2] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 2;
		}
		else
		{
			assert( false && "The passed string is not UTF-8 encoded." );
			abort( );
		}
	}
}


std::wstring tgon::UTF8_to_UTF16(
	const std::string& utf8Src )
{
	std::wstring utf16Dest( utf8Src.length( ), '\0' );

	UTF8_to_UTF16( utf8Src.c_str(), &utf16Dest[0] );
	return utf16Dest;
}

void tgon::GetFileNameFromPath(
	std::wstring* dest,
	bool deleteFileExtension )
{
	int32_t index = dest->length( )-1;
	if ( index <= 0 )
	{
        return;
	}

    if ( deleteFileExtension )
    {
        // delete file extension
		while (( *dest )[index--] != '.' )
        {
			dest->pop_back( );
        }

		// delete '.'
		dest->pop_back( );
    }
 
    // delete path
    while (( *dest )[index--] != '/' )
    {
		if ( index <= 0 )
		{
            return;
		}
    }

	dest->erase( dest->begin( ), dest->begin( )+index+2 );
}
