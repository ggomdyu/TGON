/**
* @filename    TEncoding.h
* @author      ggomdyu
* @since       04/09/2017
*/

#pragma once
#include "../Platform/TConfig.h"

#include <string>
#include <cstdint>

namespace tgon
{

class TGON_API TEncoding
{
/**
 * @section Ctor/Dtor
 */
public:
    TEncoding() = delete;
    ~TEncoding() = delete;

private:
    template <typename EncodeFromTy>
    struct TEncoder
    {
    public:
        template <typename EncodeToTy>
        static bool Convert(const char* src, char* dest);
    };

public:
    struct UTF8 : public TEncoder<UTF8> {};
    struct UTF16LE : public TEncoder<UTF16LE> {};
    struct UTF16BE : public TEncoder<UTF16BE> {};
    struct EUC_KR : public TEncoder<UTF16BE> {};

/**
 * @section Public command methods
 */
public:
    /**
     * @brief   Converts a string to another encoded.
     * @return  True if conversion is successful, or false
     */
    static bool Convert(UTF8, UTF16LE, const char* src, char* dest);

};

template<typename EncodeFromTy>
template<typename EncodeToTy>
inline bool TEncoding::TEncoder<EncodeFromTy>::Convert(const char* src, char* dest)
{
    return TEncoding::Convert(EncodeFromTy{}, EncodeToTy{}, src, dest);
}

}