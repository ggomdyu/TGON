/**
 * @file    DelegateChain.h
 * @author  ggomdyu
 * @since   06/30/2018
 * @brief   The list that contains delegates.
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
/**@section Type */
public:
    using DelegateType = Delegate<_ReturnType(_ArgTypes...)>;
    using ReturnType = _ReturnType;

/**@section Constructor */
public:
    DelegateChain() noexcept = default;

    explicit DelegateChain(const std::initializer_list<DelegateType>& initializerList);
    
    template <typename _DelegateContainer>
    explicit DelegateChain(_DelegateContainer&& delegateContainer);

/**@section Operator */
public:
    template <typename _DelegateType>
    DelegateChain& operator+=(_DelegateType&& rhs);
    DelegateChain& operator-=(const DelegateType& rhs);
    DelegateChain& operator=(std::nullptr_t rhs) noexcept;
    bool operator==(std::nullptr_t rhs) const noexcept;
    bool operator!=(std::nullptr_t rhs) const noexcept;
    template <typename... _ArgTypes2>
    _ReturnType operator()(_ArgTypes2&&... args);

/**@section Method */
public:
    /**
     * @brief   Invokes all delegates stored in list.
     * @param [in] args     The parameters of delegate to invoke.
     * @return  Returns a finally invoked delegate's return value.
     */
    template <typename... _ArgTypes2>
    _ReturnType Invoke(_ArgTypes2&&... args);

    /**
     * @brief   Inserts a delegate into the list.
     * @param [in] delegate     A delegate to insert.
     */
    template <typename _DelegateType>
    void Append(_DelegateType&& delegate);

    /**
     * @brief   Erases the delegate stored into the list.
     * @param [in] delegate     The delegate to erase.
     * @details The specified delegate's stub pointer must be matched with stored delegate in list.
     */
    bool Erase(const DelegateType& delegate);

    /**@brief   Erases all delegates stored in list. */
    void Clear() noexcept;

    /**@brief   Gets the delegate list. */
    const std::vector<DelegateType>& GetInvocationList() const noexcept;

/**@section Variable */
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

template <typename _ReturnType, typename... _ArgTypes>
template <typename _DelegateType>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator+=(_DelegateType&& rhs)
{
    this->Append(std::forward<_DelegateType>(rhs));
    return *this;
}
    
template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator-=(const DelegateType& rhs)
{
    this->Erase(rhs);
    return *this;
}
    
template <typename _ReturnType, typename... _ArgTypes>
inline DelegateChain<_ReturnType(_ArgTypes...)>& DelegateChain<_ReturnType(_ArgTypes...)>::operator=(std::nullptr_t rhs) noexcept
{
    this->Clear();
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline bool DelegateChain<_ReturnType(_ArgTypes...)>::operator==(std::nullptr_t rhs) const noexcept
{
    return m_invocationList.empty();
}

template <typename _ReturnType, typename... _ArgTypes>
inline bool DelegateChain<_ReturnType(_ArgTypes...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return !this->operator==(rhs);
}
    
template <typename _ReturnType, typename... _ArgTypes>
template <typename... _ArgTypes2>
inline _ReturnType DelegateChain<_ReturnType(_ArgTypes...)>::operator()(_ArgTypes2&&... args)
{
    return this->Invoke(std::forward<_ArgTypes2>(args)...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename... _ArgTypes2>
inline _ReturnType DelegateChain<_ReturnType(_ArgTypes...)>::Invoke(_ArgTypes2&&... args)
{
    if (m_invocationList.empty() == true)
    {
        return _ReturnType();
    }

    for (auto i = 0; i < m_invocationList.size() - 1; ++i)
    {
        m_invocationList[i](std::forward<_ArgTypes2>(args)...);
    }

    auto iter = m_invocationList.end() - 1;
    return (*iter)(std::forward<_ArgTypes2>(args)...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _DelegateType>
inline void DelegateChain<_ReturnType(_ArgTypes...)>::Append(_DelegateType&& delegate)
{
    m_invocationList.push_back(std::forward<_DelegateType>(delegate));
}

template <typename _ReturnType, typename... _ArgTypes>
inline bool DelegateChain<_ReturnType(_ArgTypes...)>::Erase(const DelegateType& delegate)
{
    auto iter = std::find_if(m_invocationList.begin(), m_invocationList.end(), [&](const DelegateType& rhs)
    {
        return delegate == rhs;
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

template <typename _ReturnType, typename... _ArgTypes>
inline void DelegateChain<_ReturnType(_ArgTypes...)>::Clear() noexcept
{
    m_invocationList.clear();
}

template <typename _ReturnType, typename... _ArgTypes>
inline const std::vector<Delegate<_ReturnType(_ArgTypes...)>>& DelegateChain<_ReturnType(_ArgTypes...)>::GetInvocationList() const noexcept
{
    return m_invocationList;
}

} /* namespace tgon */
