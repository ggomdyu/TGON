/**
 * @file    DelegateChain.h
 * @author  ggomdyu
 * @since   06/30/2018
 * @see     https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
 */

#pragma once
#include <vector>
#include <initializer_list>

#include "Delegate.h"

namespace tgon
{

template <typename>
class DelegateChain;
    
template <typename _ReturnType, typename... _ArgTypes>
class DelegateChain<_ReturnType(_ArgTypes...)> final
{
/* @section Public type */
public:
    using ValueType = Delegate<_ReturnType(_ArgTypes...)>;
    using ReturnType = _ReturnType;

/* @section Public constructor */
public:
    explicit DelegateChain(const std::initializer_list<ValueType>& initializerList);
    
    template <typename _DelegateContainer>
    explicit DelegateChain(_DelegateContainer&& delegateContainer);

/* @section Public operator */
public:
    DelegateChain& operator+=(const ValueType& rhs);
    DelegateChain& operator+=(ValueType&& rhs);
    DelegateChain& operator-=(const ValueType& rhs);

/* @section Public method */
public:
    ReturnType Invoke();
    void Append();
    void Clear();
    const std::vector<ValueType>& GetInvocationList() const;

/* @section Private variable */
private:
    std::vector<ValueType> m_invocationList;
};
    
template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>::DelegateChain(const std::initializer_list<ValueType>& initializerList) :
    m_invocationList(initializerList)
{
}
    
template <typename _ReturnType, typename... _ArgTypes>
template <typename _DelegateContainer>
inline DelegateChain<_ReturnType(_ArgTypes...)>::DelegateChain(_DelegateContainer&& delegateContainer) :
    m_invocationList(delegateContainer)
{
}
    
template <typename _ReturnType, typename... _ArgTypes>
inline _ReturnType DelegateChain<_ReturnType(_ArgTypes...)>::Invoke()
{
}

} /* namespace tgon */
