/**
 * @filename    TypeTraits.h
 * @author      ggomdyu
 * @since       05/24/2016
 * @brief       The traits for function provides information about given type in compile time.
 */

#pragma once
#include <type_traits>

namespace tgon
{
namespace utility
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

/* @brief   Traits for class member function */
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

/* @brief   Traits for lambda */
template <typename _FunctionType>
struct FunctionTraits :
    public FunctionTraits<decltype(&_FunctionType::operator())>
{
};

template <typename _ConvertFromType, typename _ConvertToType>
using EnableIfConvertible = typename std::enable_if<std::is_convertible<_ConvertFromType, _ConvertToType>::value>::type;

template <typename _ValueType>
using EnableIfFloatingPoint = typename std::enable_if<std::is_floating_point<_ValueType>::value>::type;

template <typename _ValueType>
using EnableIfArithmetic = typename std::enable_if<std::is_arithmetic<_ValueType>::value>::type;

} /* namespace utility */
} /* namespace tgon */
