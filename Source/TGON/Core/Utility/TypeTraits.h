/**
 * @filename    TypeTraits.h
 * @author      ggomdyu
 * @since       05/24/2016
 * @desc        The traits for function provides information about given type in compile time.
 */

#pragma once
#include <type_traits>

namespace tgon
{
namespace utility
{

template <typename>
struct FunctionTraits;

/* @brief   Traits for global function */
template <typename _ReturnType, typename... _Args>
struct FunctionTraits<_ReturnType(_Args...)>
{
	enum { ArgumentCount = sizeof...(_Args), };

	using ReturnType = _ReturnType;

    using FunctionType = _ReturnType(_Args...);
    using FunctionPtrType = _ReturnType(*)(_Args...);
};

template <typename _ReturnType, typename... _Args>
struct FunctionTraits<_ReturnType(*)(_Args...)> :
	public FunctionTraits<_ReturnType(_Args...)>
{
};

/* @brief   Traits for class member function */
template <typename _ReturnType, typename _ClassType, typename... _Args>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Args...)> :
	public FunctionTraits<_ReturnType(_Args...)>
{
	using ClassType = _ClassType;
};

template <typename _ReturnType, typename _ClassType, typename... _Args>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Args...) const> :
	public FunctionTraits<_ReturnType(_ClassType::*)(_Args...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _Args>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Args...) volatile> :
	public FunctionTraits<_ReturnType(_ClassType::*)(_Args...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _Args>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Args...) const volatile> :
    public FunctionTraits<_ReturnType(_ClassType::*)(_Args...)>
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
