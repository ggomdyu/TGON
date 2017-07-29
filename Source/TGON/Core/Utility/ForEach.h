/**
 * @filename    ForEach.h
 * @author      ggomdyu
 * @since       07/28/2017
 */

#include <tuple>

namespace tgon
{

template <std::size_t _Index = 0,  typename _CallbackType, typename... _Args>
inline typename std::enable_if<_Index == sizeof...(_Args)>::type ForEach(std::tuple<_Args...>& tuple, const _CallbackType& callback) noexcept
{
}

template <std::size_t _Index = 0,  typename _CallbackType, typename... _Args>
inline typename std::enable_if<_Index < sizeof...(_Args)>::type ForEach(std::tuple<_Args...>& tuple, const _CallbackType& callback) noexcept
{
    callback(std::get<_Index>(tuple));
    ForEach<_Index + 1, _CallbackType, _Args...>(tuple, callback);
}

}
