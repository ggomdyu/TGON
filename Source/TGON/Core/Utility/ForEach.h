/**
 * @filename    ForEach.h
 * @author      ggomdyu
 * @since       07/28/2017
 */

#include <tuple>

namespace tgon
{
namespace utility
{

template <std::size_t _Index = 0,  typename _CallbackType, typename... _ArgTypes>
inline typename std::enable_if<_Index == sizeof...(_ArgTypes)>::type ForEach(std::tuple<_ArgTypes...>& tuple, const _CallbackType& callback) noexcept
{
}

template <std::size_t _Index = 0,  typename _CallbackType, typename... _ArgTypes>
inline typename std::enable_if<_Index < sizeof...(_ArgTypes)>::type ForEach(std::tuple<_ArgTypes...>& tuple, const _CallbackType& callback) noexcept
{
    callback(std::get<_Index>(tuple));
    ForEach<_Index + 1, _CallbackType, _ArgTypes...>(tuple, callback);
}

} /* namespace utility */
} /* namespace tgon */
