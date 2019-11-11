/**
 * @file    FontFactory.h
 * @author  ggomdyu
 * @since   06/01/2019
 */

#pragma once
#include "Font.h"

namespace tgon
{

class TGON_API FontFactory :
    private NonCopyable
{
/**@section Constructor */
public:
    FontFactory();

/**@section Destructor */
public:
    ~FontFactory();

/**@section Method */
public:
    FT_Library GetFTLibrary() noexcept;
    const FT_Library GetFTLibrary() const noexcept;

/**@section Variable */
private:
    FT_Library m_library;
};

} /* namespace tgon */
