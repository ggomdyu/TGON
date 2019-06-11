#include "PrecompiledHeader.h"

#include "Encoding.h"

namespace tgon
{
namespace
{

enum BitsToHex
{
    _00000000 = 0x0,
    _10000000 = 0x80,
    _11000000 = 0xC0,
    _11100000 = 0xE0,
    _11110000 = 0xF0,
    _00011111 = 0x1F,
    _00111111 = 0x3F,
};

} /* namespace */

int32_t ASCII::GetCharCount(const char* str)
{
    return strlen(str);
}

int32_t UTF8::GetCharCount(const char* str)
{
    int32_t chCount = 0;

    while ( str[0] != '\0' )
    {
        if ( ( str[0] & BitsToHex::_10000000 ) == 0 )
        {
            str += 1;
        }
        else if ( ( str[0] & BitsToHex::_11100000 ) == BitsToHex::_11000000 )
        {
            str += 2;
        }
        else if ( ( str[0] & BitsToHex::_11110000 ) == BitsToHex::_11100000 )
        {
            str += 3;
        }

        ++chCount;
    }
    //Todo: Check surrogate?
    return chCount;
}

int32_t UTF16LE::GetCharCount(const char* str)
{
    return wcslen(reinterpret_cast<const wchar_t*>(str));
}

// 옛날에 짰던 코드인데 겁나느림
// 근데 필요할까봐 다시 복구
//TGON_API int32_t ConvertUTF8ToUTF16( const char* src, char* dest )
//{
//    enum BitTable
//    {
//        _00000000 = 0x0,
//        _10000000 = 0x80,
//        _11000000 = 0xC0,
//        _11100000 = 0xE0,
//        _00011111 = 0x1F,
//        _00111111 = 0x3F,
//    };
//
//    std::size_t destIndex = 0;
//    char16_t* castedDest = reinterpret_cast<char16_t*>( dest );
//
//    std::size_t i = 0;
//    while ( src[i] != u8'\0' )
//    {
//        // 000000 ~ 00007F: ASCII compatible area
//        if ( ( src[i] & _10000000 ) == _00000000 )
//        {
//            castedDest[destIndex++] = src[i];
//            ++i;
//        }
//        // 000080 ~ 0007FF: European
//        else if ( ( src[i] & _11100000 ) == _11000000 &&
//            ( src[i + 1] & _11000000 ) == _10000000 )
//        {
//            castedDest[destIndex++] = ( ( src[i] & _00011111 ) << 6 ) +
//                ( src[i + 1] & _00111111 );
//            i += 2;
//        }
//        // 000800 ~ 00FFFF: Asian
//        else if ( ( src[i] & _11100000 ) == _11100000 &&
//            ( src[i + 1] & _11000000 ) == _10000000 &&
//            ( src[i + 2] & _11000000 ) == _10000000 )
//        {
//            castedDest[destIndex++] = ( src[i] << 12 ) +
//                ( ( src[i + 1] & _00111111 ) << 6 ) +
//                ( src[i + 2] & _00111111 );
//            i += 3;
//        }
//        else
//        {
//            return -1;
//        }
//    }
//
//    castedDest[destIndex] = u8'\0';
//
//    return destIndex;
//}


} /* namespace tgon */
