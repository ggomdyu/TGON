/**
 * @filename    EncodingFwd.h
 * @author      ggomdyu
 * @since       02/20/2018
 */

#pragma once

namespace tgon
{
namespace core
{

class ASCII;
class EUC_KR;
class UTF8;
class UTF16LE;
template <typename _DerivedEncodingType>
class EUCEncoding;
template <typename _DerivedEncodingType>
class UnicodeEncoding;

} /* namespace core */
} /* namespace tgon */