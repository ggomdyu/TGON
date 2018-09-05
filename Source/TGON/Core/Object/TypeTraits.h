/**
 * @file    TypeTraits.h
 * @author  ggomdyu
 * @since   05/24/2016
 * @brief   The traits that provides information about given type in compile time.
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
    enum { ArgumentCount = sizeof...(_ArgTypes), };

    using ReturnType = _ReturnType;

    using FunctionType = _ReturnType(_ArgTypes...);
    using FunctionPtrType = _ReturnType(*)(_ArgTypes...);
};

template <typename _ReturnType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(*)(_ArgTypes...)> :
    public FunctionTraits<_ReturnType(_ArgTypes...)>
{
};

/* @brief   Traits for the class member function */
template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)> :
    public FunctionTraits<_ReturnType(_ArgTypes...)>
{
    using ClassType = _ClassType;
};

template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) const> :
    public FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) volatile> :
    public FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _ArgTypes>
struct FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...) const volatile> :
    public FunctionTraits<_ReturnType(_ClassType::*)(_ArgTypes...)>
{
};

/* @brief   Traits for the lambda */
template <typename _FunctionType>
struct FunctionTraits :
    public FunctionTraits<decltype(&_FunctionType::operator())>
{
};
    
template <typename _Type>
constexpr auto IsPureType = std::integral_constant<bool,
    !std::is_const<_Type>::value &&
    !std::is_volatile<_Type>::value &&
    !std::is_reference<_Type>::value &&
    !std::is_pointer<_Type>::value>::value;
    
template <typename _Type>
using PurifyType = typename std::decay<typename std::remove_pointer<typename std::remove_volatile<_Type>::type>::type>::type;
    

} /* namespace tgon */
