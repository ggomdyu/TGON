/**
 * @file    TypeTraits.h
 * @author  ggomdyu
 * @since   05/24/2016
 * @brief   The set of type utilities.
 */

#pragma once
#include <type_traits>
#include <string>

namespace tgon
{

template <typename>
struct FunctionTraits;

template <typename _ReturnType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ArgTypes...)>
{
/**@section Enum */
public:
    enum { ArgumentCount = sizeof...(_ArgTypes), };

/**@section Type */
public:
    using ReturnType = _ReturnType;
    using FunctionType = _ReturnType(_ArgTypes...);
    using FunctionPtrType = _ReturnType(*)(_ArgTypes...);
};

/**@brief   Traits for the global function */
template <typename _ReturnType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(*)(_ArgTypes...)> : FunctionTraits<_ReturnType(_ArgTypes...)>
{
};

/**@brief   Traits for the class member function */
template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)> :
    FunctionTraits<std::remove_cv_t<_ReturnType(_ArgTypes...)>>
{
/**@section Type */
    using ClassType = _ClassType;
};

template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) const> :
    FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};
    
template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) volatile> :
    FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) const volatile> :
    FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};

/**@brief   Traits for the lambda */
template <typename _FunctionType>
struct FunctionTraits : FunctionTraits<decltype(&_FunctionType::operator())> {};

template <typename>
struct IsBasicString : std::false_type {};

template <typename _CharType, typename _TraitsType, typename _AllocatorType>
struct IsBasicString<std::basic_string<_CharType, _TraitsType, _AllocatorType>> : std::true_type {};

template <typename>
struct IsBasicStringView : std::false_type {};

template <typename _CharType>
struct IsBasicStringView<std::basic_string_view<_CharType>> : std::true_type {};

template <typename _Type>
class RemoveAllPointers
{
    /**@section Type */
public:
    using Type = _Type;
};

template <typename _Type>
class RemoveAllPointers<_Type*>
{
    /**@section Type */
public:
    using Type = typename RemoveAllPointers<_Type>::Type;
};

template <typename _Type>
using RemoveAllPointers_t = typename RemoveAllPointers<_Type>::Type;

template <typename _Type>
using Pure_t = std::remove_cv_t<RemoveAllPointers_t<std::decay_t<_Type>>>;

template <typename _Type, typename... _Types>
constexpr bool IsAllSame_v = std::bool_constant<(std::is_same_v<_Type, _Types> && ...)>::value;

template <typename _Type, typename... _Types>
constexpr bool IsAny_v = std::bool_constant<(std::is_same_v<_Type, _Types> || ...)>::value;

template <typename _Type>
constexpr bool IsPure_v = std::is_same_v<Pure_t<_Type>, _Type>;

template <typename _Type>
constexpr bool IsChar_v = IsAny_v<_Type, char, char16_t, char32_t, wchar_t>;
    
template <typename _Type>
constexpr bool IsCharPointer_v = IsChar_v<Pure_t<_Type>> && (std::is_pointer_v<_Type> || std::is_reference_v<_Type>);

template <typename _Type>
constexpr bool IsBasicString_v = IsBasicString<_Type>::value;

template <typename _Type>
constexpr bool IsBasicStringView_v = IsBasicStringView<_Type>::value;

} /* namespace tgon */
