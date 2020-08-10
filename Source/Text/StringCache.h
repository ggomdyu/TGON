#pragma once

#include <unordered_set>
#include <string>
#include <string_view>

namespace tg
{

template <typename _Char>
class StringCache final
{
/**@section Type */
public:
    using CharType = _Char;

/**@section Constructor */
public:
    [[nodiscard]] std::basic_string<_Char>& GetValue(std::basic_string<_Char> str);

/**@section Variable */
private:
    std::unordered_set<std::basic_string<_Char>> m_strCache;
};

template <typename _Char>
inline std::basic_string<_Char>& StringCache<_Char>::GetValue(std::basic_string<_Char> str)
{
    auto ret = m_strCache.insert(std::move(str));
    if (ret.second == false)
    {
        return *ret.first;
    }
}

}
