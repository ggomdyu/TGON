/**
 * @filename    TypeTraits.h
 * @author      ggomdyu
 * @since       05/24/2016
 * @desc        The traits for function provides information about given type in compile time.
 */

#pragma once
#include <type_traits>
#include <tuple>

namespace tgon
{
namespace utility
{

template <typename>
struct FunctionTraits;

/* @brief   Traits for global function */
template <typename _ReturnType, typename... _Params>
struct FunctionTraits<_ReturnType(_Params...)>
{
	using ReturnType = _ReturnType;

    using FunctionType = _ReturnType(_Params...);
    using FunctionPtrType = _ReturnType(*)(_Params...);

    enum { ParameterCount = sizeof...(_Params), };
    using ParameterPackType = std::tuple<_Params...>;
};

template <typename _ReturnType, typename... _Params>
struct FunctionTraits<_ReturnType(*)(_Params...)> :
	public FunctionTraits<_ReturnType(_Params...)>
{
};

/* @brief   Traits for class member function */
template <typename _ReturnType, typename _ClassType, typename... _Params>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Params...)> :
	public FunctionTraits<_ReturnType(_Params...)>
{
	using ClassType = _ClassType;
};

template <typename _ReturnType, typename _ClassType, typename... _Params>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Params...) const> :
	public FunctionTraits<_ReturnType(_ClassType::*)(_Params...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _Params>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Params...) volatile> :
	public FunctionTraits<_ReturnType(_ClassType::*)(_Params...)>
{
};

template <typename _ReturnType, typename _ClassType, typename... _Params>
struct FunctionTraits<_ReturnType(_ClassType::*)(_Params...) const volatile> :
    public FunctionTraits<_ReturnType(_ClassType::*)(_Params...)>
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
