#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"

#include "FontFactory.h"

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  {e, s},
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       {0, 0}};

namespace tgon
{

const char* ConvertFTErrorToString(FT_Error error)
{
    static constexpr const struct
    {
        int errorCode;
        const char* errorMessage;
    } ftErrors[] =
    #include FT_ERRORS_H
    
    return ftErrors[error].errorMessage;
}

constexpr int32_t ConvertFTPixelModeToBits(FT_Pixel_Mode pixelMode) noexcept
{
    constexpr int32_t bytesTable[] =
    {
        1, // FT_PIXEL_MODE_MONO
        8, // FT_PIXEL_MODE_GRAY
        2, // FT_PIXEL_MODE_GRAY2
        4, // FT_PIXEL_MODE_GRAY4
        8, // FT_PIXEL_MODE_LCD
        8, // FT_PIXEL_MODE_LCD_V
        32, // FT_PIXEL_MODE_BGRA
    };

    return bytesTable[static_cast<int32_t>(pixelMode)];
}

FontFactory::FontFactory() :
    m_library(nullptr)
{
    FT_Error error = FT_Init_FreeType(&m_library) != 0;
    if (error)
    {
        Debug::Fail("Failed to invoke FT_Init_FreeType.", ConvertFTErrorToString(error));
    }
}

FontFactory::~FontFactory()
{
    if (m_library != nullptr)
    {
        FT_Done_FreeType(m_library);
        m_library = nullptr;
    }
}

FT_Library FontFactory::GetFTLibrary() noexcept
{
    return m_library;
}

const FT_Library FontFactory::GetFTLibrary() const noexcept
{
    return m_library;
}

} /* namespace tgon */

#undef FT_ERRORDEF
#undef FT_ERROR_START_LIST
#undef FT_ERROR_END_LIST
