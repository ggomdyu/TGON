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

/* @brief   Trait for lambda */
template <typename Ty>
struct FunctionTraits : 
	public FunctionTraits<decltype(&Ty::operator())>
{
public:
    FunctionTraits() = delete;
    ~FunctionTraits() = delete;
};

/* @brief   Trait for global function */
template <typename _ReturnTy, typename... Args>
struct FunctionTraits<_ReturnTy(Args...)>
{
public:
    FunctionTraits() = delete;
    ~FunctionTraits() = delete;

public:
	enum { ArgumentCount = sizeof...(Args), };

	using ReturnTy = _ReturnTy;
    using FunctionTy = _ReturnTy(Args...);
    using FunctionPtrTy = _ReturnTy(*)(Args...);
};

template <typename ReturnTy, typename... Args>
struct FunctionTraits<ReturnTy(*)(Args...)> :
	public FunctionTraits<ReturnTy(Args...)>
{
};

/* @brief   Trait for class member function */
template <typename ReturnTy, typename _ClassTy, typename... Args>
struct FunctionTraits<ReturnTy(_ClassTy::*)(Args...)> :
	public FunctionTraits<ReturnTy(Args...)>
{
public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct FunctionTraits<ReturnTy(_ClassTy::*)(Args...) const> :
	public FunctionTraits<ReturnTy(Args...)>
{
public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct FunctionTraits<ReturnTy(_ClassTy::*)(Args...) volatile> :
	public FunctionTraits<ReturnTy(Args...)>
{
public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct FunctionTraits<ReturnTy(_ClassTy::*)(Args...) const volatile> :
    public FunctionTraits<ReturnTy(Args...)>
{
public:
    using ClassTy = _ClassTy;
};

/* @brief   Enable if */
template <typename ConvertFromTy, typename ConvertToTy>
using EnableIfConvertible = typename std::enable_if<std::is_convertible<ConvertFromTy, ConvertToTy>::value>::type;

template <typename Ty>
using EnableIfFloatingPoint = typename std::enable_if<std::is_floating_point<Ty>::value>::type;

template <typename Ty>
using EnableIfArithmetic = typename std::enable_if<std::is_arithmetic<Ty>::value>::type;

} /* namespace utility */
} /* namespace tgon */
