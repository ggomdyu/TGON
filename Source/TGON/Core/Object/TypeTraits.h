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

/**@brief   Traits for the class member function */
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

/**@brief   Traits for the lambda */
template <typename _FunctionType>
struct FunctionTraits :
    public FunctionTraits<decltype(&_FunctionType::operator())>
{
};
    
template <typename _Type>
constexpr bool IsPureType = !std::is_const<_Type>::value && 
                            !std::is_volatile<_Type>::value && 
                            !std::is_reference<_Type>::value && 
                            !std::is_pointer<_Type>::value;
    
template <typename _Type>
using PurifyType = std::decay_t<std::remove_pointer_t<std::remove_volatile_t<_Type>>>;
    

} /* namespace tgon */
