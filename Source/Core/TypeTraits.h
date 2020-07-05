#pragma once

#include <type_traits>
#include <string>

namespace tg
{
namespace detail
{

template <typename>
struct IsBasicString : std::false_type {};

template <typename _Char, typename _Traits, typename _Allocator>
struct IsBasicString<std::basic_string<_Char, _Traits, _Allocator>> : std::true_type {};

template <typename>
struct IsBasicStringView : std::false_type {};

template <typename _Char>
struct IsBasicStringView<std::basic_string_view<_Char>> : std::true_type {};

template <typename _Type>
struct RemoveAllPointers
{
    using Type = _Type;
};

template <typename _Type>
struct RemoveAllPointers<_Type*>
{
    using Type = typename RemoveAllPointers<_Type>::Type;
};

}

template <typename>
struct FunctionTraits;

template <typename _Return, typename... _Args>
struct FunctionTraits<_Return(_Args...)>
{
/**@section Type */
public:
    using ReturnType = _Return;
    using FunctionType = _Return(_Args...);
    
/**@section Variable */
public:
    static constexpr bool IsMemberFunction = false;
    static constexpr bool IsFunctor = false;
    static constexpr size_t ArgumentCount = sizeof...(_Args);
};

template <typename _Return, typename... _Args>
struct FunctionTraits<_Return(*)(_Args...)> : FunctionTraits<_Return(_Args...)> {};

template <typename _Return, typename _Class, typename... _Args>
struct FunctionTraits<_Return(_Class::*)(_Args...)> :
    FunctionTraits<std::remove_cv_t<_Return(_Args...)>>
{
/**@section Type */
public:
    using ClassType = _Class;
    
/**@section Variable */
public:
    static constexpr bool IsMemberFunction = true;
};

template <typename _Return, typename _Class, typename... _Args>
struct FunctionTraits<_Return(_Class::*)(_Args...) const> : FunctionTraits<_Return(_Class::*)(_Args...)> {};
    
template <typename _Return, typename _Class, typename... _Args>
struct FunctionTraits<_Return(_Class::*)(_Args...) volatile> : FunctionTraits<_Return(_Class::*)(_Args...)> {};

template <typename _Return, typename _Class, typename... _Args>
struct FunctionTraits<_Return(_Class::*)(_Args...) const volatile> : FunctionTraits<_Return(_Class::*)(_Args...)> {};

template <typename _Function>
struct FunctionTraits :
    FunctionTraits<decltype(&_Function::operator())>
{
/**@section Variable */
public:
    static constexpr bool IsFunctor = true;
    static constexpr bool IsMemberFunction = false;
};

template <typename _Type>
constexpr bool IsBasicString = detail::IsBasicString<_Type>::value;

template <typename _Type>
constexpr bool IsBasicStringView = detail::IsBasicStringView<_Type>::value;

template <typename _Type>
using RemoveAllPointers = typename detail::RemoveAllPointers<_Type>::Type;

template <typename _Type>
using Pure = std::remove_cv_t<RemoveAllPointers<std::decay_t<_Type>>>;

template <typename _Type>
constexpr bool IsPure = std::is_same_v<Pure<_Type>, _Type>;

template <typename _Type, typename... _Types>
constexpr bool IsAllSame = std::bool_constant<(std::is_same_v<_Type, _Types> && ...)>::value;

template <typename _Type, typename... _Types>
constexpr bool IsAny = std::bool_constant<(std::is_same_v<_Type, _Types> || ...)>::value;

template <typename _Type>
constexpr bool IsChar = IsAny<_Type, char, char16_t, char32_t, wchar_t>;
    
template <typename _Type>
constexpr bool IsCharPointer = IsChar<Pure<_Type>> && std::is_pointer_v<_Type>;

template <typename _Type>
constexpr bool IsCharReference = IsChar<Pure<_Type>> && std::is_reference_v<_Type>;

}
