#pragma once

#include <optional>

#include "Font.h"

namespace tg
{

class FontFactory final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(FontFactory)

/**@section Constructor */
private:
    explicit FontFactory(FT_Library library) noexcept;

/**@section Method */
public:
    static std::optional<FontFactory> Create();
    template <typename _ContainerType>
    std::shared_ptr<Font> CreateFont(_ContainerType&& fileData) const;
    std::shared_ptr<Font> CreateFont(const char* filePath) const;

/**@section Variable */
private:
    std::shared_ptr<FT_LibraryRec> m_library;
};

template<typename _ContainerType>
inline std::shared_ptr<Font> FontFactory::CreateFont(_ContainerType&& fileData) const
{
    return std::make_shared<Font>(m_library, std::forward<_ContainerType>(fileData));
}

}
