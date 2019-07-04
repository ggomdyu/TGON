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
struct FunctionTraits<_ReturnType(*)(_ArgTypes...)> : FunctionTraits<_ReturnType(_ArgTypes...)> {};

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
using RemoveAllPointersType = typename RemoveAllPointers<_Type>::Type;

template <typename _Type>
constexpr bool IsPureTypeValue = !std::is_const<_Type>::value && 
                                 !std::is_volatile<_Type>::value && 
                                 !std::is_reference<_Type>::value && 
                                 !std::is_pointer<_Type>::value;
    
template <typename _Type>
using PureType = std::remove_cv_t<RemoveAllPointersType<std::decay_t<_Type>>>;

template <typename _Type>
constexpr bool IsCharValue = std::is_same<_Type, char>::value ||
std::is_same<_Type, char16_t>::value ||
std::is_same<_Type, char32_t>::value ||
std::is_same<_Type, wchar_t>::value;
    
template <typename _Type>
constexpr bool IsCharPointerValue = IsCharValue<PureType<_Type>> && (std::is_pointer_v<_Type> || std::is_reference_v<_Type>);

template <typename>
struct IsBasicString : std::false_type {};

template <typename _CharType, typename _TraitsType, typename _AllocatorType>
struct IsBasicString<std::basic_string<_CharType, _TraitsType, _AllocatorType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicStringValue = IsBasicString<_Type>::value;

template <typename>
struct IsBasicStringView : std::false_type {};

template <typename _CharType>
struct IsBasicStringView<std::basic_string_view<_CharType>> : std::true_type {};

template <typename _Type>
constexpr bool IsBasicStringViewValue = IsBasicStringView<_Type>::value;

} /* namespace tgon */
