#include "PrecompiledHeader.h"
#include "TString.h"

namespace tgon {
namespace core {

bool ConvertUTF_8ToUTF_16( /*IN*/ const char* utf16Src, /*OUT*/ wchar_t* utf16Dest )
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
			// Error: The forwarded string is not UTF-8 encoded
			return false;
		}
	}

	return true;
}

} /* namespace core */
} /* namespace tgon */


std::wstring tgon::GetFileNameFromPath( const wchar_t* srcFileName, bool deleteFileExtension )
{
	std::wstring ret;
	return ret;

	//int32_t index = ret.length( )-1;
	//if ( index <= 0 )
	//{
 //       return;
	//}

 //   if ( deleteFileExtension )
 //   {
 //       // delete file extension
	//	while (( *dest )[index--] != '.' )
 //       {
	//		dest->pop_back( );
 //       }

	//	// delete '.'
	//	dest->pop_back( );
 //   }
 //
 //   // delete path
 //   while ( srcFileName[index--] != '/' )
 //   {
	//	if ( index <= 0 )
	//	{
 //           return;
	//	}
 //   }

	//dest->erase( dest->begin( ), dest->begin( )+index+2 );
}
