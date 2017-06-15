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
struct TFunctionTraits;

/* @brief   Trait for lambda */
template <typename Ty>
struct TFunctionTraits : 
	public TFunctionTraits<decltype(&Ty::operator())>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;
};

/* @brief   Trait for global function */
template <typename _ReturnTy, typename... Args>
struct TFunctionTraits<_ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;

public:
	enum { ArgumentCount = sizeof...(Args), };

	using ReturnTy = _ReturnTy;
    using FunctionTy = _ReturnTy(Args...);
    using FunctionPtrTy = _ReturnTy(*)(Args...);
};

template <typename ReturnTy, typename... Args>
struct TFunctionTraits<ReturnTy(*)(Args...)> :
	public TFunctionTraits<ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;
};

/* @brief   Trait for class member function */
template <typename ReturnTy, typename _ClassTy, typename... Args>
struct TFunctionTraits<ReturnTy(_ClassTy::*)(Args...)> :
	public TFunctionTraits<ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;

public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct TFunctionTraits<ReturnTy(_ClassTy::*)(Args...) const> :
	public TFunctionTraits<ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;

public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct TFunctionTraits<ReturnTy(_ClassTy::*)(Args...) volatile> :
	public TFunctionTraits<ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;

public:
	using ClassTy = _ClassTy;
};

template <typename ReturnTy, typename _ClassTy, typename... Args>
struct TFunctionTraits<ReturnTy(_ClassTy::*)(Args...) const volatile> :
    public TFunctionTraits<ReturnTy(Args...)>
{
public:
    TFunctionTraits() = delete;
    ~TFunctionTraits() = delete;

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
