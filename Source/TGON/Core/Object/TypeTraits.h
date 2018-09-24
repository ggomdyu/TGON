/**
 * @file    TypeTraits.h
 * @author  ggomdyu
 * @since   05/24/2016
 * @brief   The set of type utilities.
 */

#pragma once
#include <type_traits>

namespace tgon
{

template <typename>
struct FunctionTraits;

template <typename _ReturnType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ArgTypes...)>
{
/**@section Public enum */
public:
    enum { ArgumentCount = sizeof...(_ArgTypes), };

/**@section Public type */
public:
    using ReturnType = _ReturnType;
    using FunctionType = _ReturnType(_ArgTypes...);
    using FunctionPtrType = _ReturnType(*)(_ArgTypes...);
};

/**@brief   Traits for the global function */
template <typename _ReturnType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(*)(_ArgTypes...)> : FunctionTraits<_ReturnType(_ArgTypes...)> {};

/**@brief   Traits for the class member function */
template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)> :
    FunctionTraits<std::remove_cv_t<_ReturnType(_ArgTypes...)>>
{
/**@section Public type */
    using ClassType = _ClassType;
};

/**@brief   Traits for the lambda */
template <typename _FunctionType>
struct FunctionTraits : FunctionTraits<decltype(&_FunctionType::operator())> {};

template <typename _Type>
class RemoveAllPointers
{
/**@section Public type */
public:
    using Type = _Type;
};

template <typename _Type>
class RemoveAllPointers<_Type*>
{
/**@section Public type */
public:
    using Type = typename RemoveAllPointers<_Type>::Type;
};

template <typename _Type>
using RemoveAllPointersType = typename RemoveAllPointers<_Type>::Type;

template <typename _Type>
constexpr bool IsPureTypeValue = !std::is_const<_Type>::value && 
                                 !std::is_volatile<_Type>::value && 
                                 !std::is_reference<_Type>::value && 
                                 !std::is_pointer<_Type>::value;
    
template <typename _Type>
using PurifyType = std::decay_t<RemoveAllPointersType<std::remove_cv_t<_Type>>>;

template <typename _Type>
constexpr bool IsCharTypeValue = std::is_same<_Type, char>::value ||
                                 std::is_same<_Type, char16_t>::value ||
                                 std::is_same<_Type, char32_t>::value ||
                                 std::is_same<_Type, wchar_t>::value;

template <typename>
struct IsBasicString : std::false_type {};

template <typename _CharType, typename _TraitsType, typename _AllocatorType>
struct IsBasicString<std::basic_string<_CharType, _TraitsType, _AllocatorType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicStringValue = IsBasicString<_Type>::value;

} /* namespace tgon */
