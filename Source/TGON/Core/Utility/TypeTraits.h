/**
 * @filename    TypeTraits.h
 * @author      ggomdyu
 * @since       05/24/2016
 * @brief       The traits that provides information about given type in compile time.
 */

#pragma once
#include <type_traits>

#define TGON_ENABLE_IF(value) typename std::enable_if<value>::type* = nullptr

#define TGON_IS_SAME(type1, type2) std::is_same<type1, type2>::value
#define TGON_IS_POINTER(type) std::is_pointer<type>::value
#define TGON_IS_REFERENCE(type) std::is_reference<type>::value
#define TGON_IS_CONST(type) std::is_const<type>::value
#define TGON_IS_ARITHMETIC(type) std::is_arithmetic<type>::value
#define TGON_IS_FUNCTION(type) std::is_function<type>::value

namespace tgon
{
namespace core
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

} /* namespace core */
} /* namespace tgon */