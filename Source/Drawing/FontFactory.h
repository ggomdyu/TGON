/**
 * @file    FontFactory.h
 * @author  ggomdyu
 * @since   06/01/2019
 */

#pragma once
#include <optional>

#include "Core/Object.h"

#include "Font.h"

namespace tgon
{

class FontFactory final :
    private Object
{
public:
    TGON_DECLARE_RTTI(FontFactory)

/**@section Struct */
private:
    struct FTLibraryDeleter
    {
    /**@section Operator */
    public:
        void operator()(FT_Library library);
    };

/**@section Constructor */
public:
    FontFactory(FT_Library library) noexcept;

/**@section Operator */
public:
    FontFactory& operator=(FontFactory&& rhs) noexcept = default;

/**@section Method */
public:
    static std::optional<FontFactory> Create();
    template <typename _ContainerType>
    std::shared_ptr<Font> CreateFont(_ContainerType&& fileData);
    std::shared_ptr<Font> CreateFont(const char* filePath);

/**@section Variable */
private:
    std::unique_ptr<FT_Library, FTLibraryDeleter> m_library;
};

template<typename _ContainerType>
inline std::shared_ptr<Font> FontFactory::CreateFont(_ContainerType&& fileData)
{
    return std::make_shared<Font>(m_library, std::forward<_ContainerType>(fileData));
}

} /* namespace tgon */
