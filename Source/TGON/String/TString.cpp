#include "PrecompiledHeader.h"
#include "TString.h"

#include <cassert>

void tgon::utf8_to_utf16( const char* const utf8Src,
						  const int32_t length,
						  _Out_ wchar_t* const utf16Dest )
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

	for ( int32_t i = 0; i < length; ++i )
	{
		// 000000-00007F : America
		if (( utf8Src[i] & _1000_0000 ) == 0 )
		{
			utf16Dest[destIndex++] = utf8Src[i];
		}

		// 000080-0007FF : Europe
		else if (( utf8Src[i] & _1110_0000 ) == _1100_0000 &&
				 ( utf8Src[i+1] & _1100_0000 ) == _1000_0000 )
		{
			const wchar_t ch =
				(( utf8Src[i] & _0001_1111 ) << 6 ) +
				( utf8Src[i] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 1;
		}
		// 000800-00FFFF : Asia
		else if (( utf8Src[i] & _1110_0000 ) == _1110_0000 &&
				 ( utf8Src[i+1] & _1100_0000 ) == _1000_0000 &&
				 ( utf8Src[i+2] & _1100_0000 ) == _1000_0000 )
		{
			const wchar_t ch = 
				( utf8Src[i] << 12 ) +
				(( utf8Src[i+1] & _0011_1111 ) << 6 ) +
				( utf8Src[i+2] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 2;
		}
		else
		{
			assert( "The passed code data is not UTF-8 encoded." );
		}
	}
}


std::wstring tgon::utf8_to_utf16( const std::string& utf8Src )
{
	std::wstring utf16Dest( utf8Src.length( ), '\0' );

	utf8_to_utf16( utf8Src.c_str(),
				   utf8Src.length( ),
				   &utf16Dest[0] );

	return utf16Dest;
}

void tgon::GetFileNameFromPath( _Out_ std::wstring* outSrc,
								bool isDeleteFileExtension )
{
	int32_t index = outSrc->length( )-1;
	if ( index <= 0 )
	{
        return;
	}

 
    if ( isDeleteFileExtension )
    {
        // delete file extension
		while (( *outSrc )[index--] != '.' )
        {
			outSrc->pop_back( );
        }

		// delete '.'
		outSrc->pop_back( );
    }
 
    // delete path
    while (( *outSrc )[index--] != '/' )
    {
		if ( index <= 0 )
		{
            return;
		}
    }

	outSrc->erase( outSrc->begin( ),
				   outSrc->begin( )+index+2 );
}
