/**
 * @file    DelegateChain.h
 * @author  ggomdyu
 * @since   06/30/2018
 * @see     https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
 */

#pragma once
#include <vector>

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
    using DelegateType = _ReturnType(_ArgTypes...);

/* @section Public constructor */
public:
 
/* @section Public destructor */
public:

/* @section Public operator */
public:
    DelegateChain& operator+=(const DelegateType& rhs);
    DelegateChain& operator+=(DelegateType&& rhs);
    DelegateChain& operator-=(const DelegateType& rhs);

/* @section Public method */
public:
    
    const std::vector<DelegateType>& GetInvocationList() const;

/* @section Private variable */
private:
    std::vector<DelegateType> m_invocationList;
};

template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator+=(const Delegate<_ReturnType(_ArgTypes...)>& rhs)
{
    m_invocationList.push_back(rhs);
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator+=(Delegate<_ReturnType(_ArgTypes...)>&& rhs)
{
    m_invocationList.push_back(rhs);
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator-=(const Delegate<_ReturnType(_ArgTypes...)>& rhs)
{
    m_invocationList;
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline const std::vector<Delegate<_ReturnType(_ArgTypes...)>>& DelegateChain<_ReturnType(_ArgTypes...)>::GetInvocationList() const
{
    return m_invocationList;
}

} /* namespace tgon */
