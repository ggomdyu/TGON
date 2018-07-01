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
    using DelegateType = Delegate<_ReturnType(_ArgTypes...)>;
    using ReturnType = _ReturnType;

/* @section Public constructor */
public:
    DelegateChain() = default;

    explicit DelegateChain(const std::initializer_list<DelegateType>& initializerList);
    
    template <typename _DelegateContainer>
    explicit DelegateChain(_DelegateContainer&& delegateContainer);

/* @section Public operator */
public:
    template <typename _DelegateType>
    DelegateChain& operator+=(_DelegateType&& rhs);
    DelegateChain& operator-=(const DelegateType& rhs);

/* @section Public method */
public:
    _ReturnType Invoke(_ArgTypes&&... args);
    template <typename _DelegateType>
    void Append(_DelegateType&& value);
    bool Erase(const DelegateType& value);
    void Clear() noexcept;
    const std::vector<DelegateType>& GetInvocationList() const noexcept;

/* @section Private variable */
private:
    std::vector<DelegateType> m_invocationList;
};
    
template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>::DelegateChain(const std::initializer_list<DelegateType>& initializerList) :
    m_invocationList(initializerList)
{
}
    
template <typename _ReturnType, typename... _ArgTypes>
template <typename _DelegateContainer>
inline DelegateChain<_ReturnType(_ArgTypes...)>::DelegateChain(_DelegateContainer&& delegateContainer) :
    m_invocationList(delegateContainer)
{
}

template<typename _ReturnType, typename ..._ArgTypes>
template<typename _DelegateType>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator+=(_DelegateType&& rhs)
{
    this->Append(std::forward<_DelegateType>(rhs));
    return *this;
}
    
template<typename _ReturnType, typename ..._ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator-=(const DelegateType& rhs)
{
    this->Erase(rhs);
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline _ReturnType DelegateChain<_ReturnType(_ArgTypes...)>::Invoke(_ArgTypes&&... args)
{
    if (m_invocationList.size() <= 0)
    {
        return _ReturnType();
    }

    for (int i = 0; i < m_invocationList.size() - 1; ++i)
    {
        m_invocationList[i](std::forward<_ArgTypes>(args)...);
    }

    auto iter = m_invocationList.end() - 1;
    return (*iter)(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename ..._ArgTypes>
template<typename _DelegateType>
inline void DelegateChain<_ReturnType(_ArgTypes...)>::Append(_DelegateType&& value)
{
    m_invocationList.push_back(std::forward<_DelegateType>(value));
}

template<typename _ReturnType, typename ..._ArgTypes>
inline bool DelegateChain<_ReturnType(_ArgTypes...)>::Erase(const DelegateType& value)
{
    auto iter = std::find_if(m_invocationList.begin(), m_invocationList.end(), [&](const DelegateType& rhs)
    {
        return value == rhs;
    });

    if (iter != m_invocationList.end())
    {
        m_invocationList.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

template<typename _ReturnType, typename ..._ArgTypes>
inline void DelegateChain<_ReturnType(_ArgTypes...)>::Clear() noexcept
{
    m_invocationList.clear();
}

template<typename _ReturnType, typename ..._ArgTypes>
inline const std::vector<Delegate<_ReturnType(_ArgTypes...)>>& DelegateChain<_ReturnType(_ArgTypes...)>::GetInvocationList() const noexcept
{
    return m_invocationList;
}

} /* namespace tgon */
