/**
 * @file    FontFactory.h
 * @author  ggomdyu
 * @since   06/01/2019
 */

#pragma once
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "String/StringHash.h"

namespace tgon
{

class FontFactory
{
/**@section Constructor */
public:
    FontFactory();

/**@section Destructor */
public:
    ~FontFactory();

/**@section Method */
public:
    bool ImportFont(const StringHash& fontPath);

/**@section Variable */
private:
    FT_Library m_fontLibrary;
    std::unordered_map<StringHash, FT_Face> m_fontFaces;
};

} /* namespace tgon */
