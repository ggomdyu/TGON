#include "PrecompiledHeader.h"

#include "FontFactory.h"

namespace tgon
{

FontFactory::FontFactory()
{
}

FontFactory::~FontFactory()
{
}

bool FontFactory::ImportFont(const StringHash& fontPath)
{
    auto iter = m_fontFaces.find(fontPath);
    if (iter != m_fontFaces.end())
    {

    }

    FT_Face fontFace;
    FT_New_Face(m_fontLibrary, fontPath.CStr(), 0, &fontFace);

    m_fontFaces.insert({fontPath, fontFace});

    return false;
}

} /* namespace tgon */
