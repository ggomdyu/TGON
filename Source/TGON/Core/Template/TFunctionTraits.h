/**
 * filename TFunctionTraits.h
 * author   ggomdyu
 * since    05/24/2016
 * desc     The traits for function provides information about given type in compile time.
 */

#pragma once

namespace tgon
{

template <typename>
struct TFunctionTraits;

/* @brief Trait for lambda */
template <typename Ty>
struct TFunctionTraits : 
	public TFunctionTraits<decltype(&Ty::operator())>
{
};

/* @brief Trait for global function */
template <typename _ReturnTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(_Args...)>
{
public:
    TFunctionTraits() = delete;

public:
	enum { ArgumentCount = sizeof...(_Args), };
	using ReturnTy = _ReturnTy;
    using FunctionTy = _ReturnTy(_Args...);
    using FunctionPtrTy = _ReturnTy(*)(_Args...);
};

template <typename _ReturnTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(*)(_Args...)> :
	public TFunctionTraits<_ReturnTy(_Args...)>
{
};

/* @brief Trait for class member function */
template <typename _ReturnTy, typename _ClassTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(_ClassTy::*)(_Args...)> :
	public TFunctionTraits<_ReturnTy(_Args...)>
{
	using ClassTy = _ClassTy;
};

template <typename _ReturnTy, typename _ClassTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(_ClassTy::*)(_Args...) const> :
	public TFunctionTraits<_ReturnTy(_Args...)>
{
	using ClassTy = _ClassTy;
};

template <typename _ReturnTy, typename _ClassTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(_ClassTy::*)(_Args...) volatile> :
	public TFunctionTraits<_ReturnTy(_Args...)>
{
	using ClassTy = _ClassTy;
};

template <typename _ReturnTy, typename _ClassTy, typename... _Args>
struct TFunctionTraits<_ReturnTy(_ClassTy::*)(_Args...) const volatile> :
    public TFunctionTraits<_ReturnTy(_Args...)>
{
    using ClassTy = _ClassTy;
};

template <typename Ty>
using ReturnTy = typename TFunctionTraits<Ty>::ReturnTy;

} /* namespace tgon */