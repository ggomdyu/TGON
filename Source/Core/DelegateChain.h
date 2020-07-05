#pragma once

#include <vector>

#include "Delegate.h"

namespace tg
{

template <typename>
class DelegateChain;
    
template <typename _Return, typename... _Args>
class DelegateChain<_Return(_Args...)> final
{
/**@section Type */
public:
    using DelegateType = Delegate<_Return(_Args...)>;
    using ReturnType = _Return;

/**@section Constructor */
public:
    DelegateChain() noexcept = default;
    template <typename _Container>
    explicit DelegateChain(_Container container);

/**@section Operator */
public:
    template <typename _Delegate>
    DelegateChain& operator+=(_Delegate&& rhs);
    DelegateChain& operator-=(const DelegateType& rhs);
    DelegateChain& operator=(std::nullptr_t rhs) noexcept;
    bool operator==(std::nullptr_t rhs) const noexcept;
    bool operator!=(std::nullptr_t rhs) const noexcept;
    template <typename... _Args2>
    _Return operator()(_Args2&&... args);

/**@section Method */
public:
    template <typename... _Args2>
    _Return Invoke(_Args2&&... args);
    [[nodiscard]] const std::vector<DelegateType>& GetInvocationList() const noexcept;

/**@section Variable */
private:
    std::vector<DelegateType> m_invocationList;
};

template <typename _Return, typename... _Args>
template <typename _Container>
DelegateChain<_Return(_Args...)>::DelegateChain(_Container container) :
    m_invocationList(std::move(container))
{
}

template <typename _Return, typename... _Args>
template <typename _Delegate>
DelegateChain<_Return(_Args...)>& DelegateChain<_Return(_Args...)>::operator+=(_Delegate&& rhs)
{
    m_invocationList.push_back(std::forward<_Delegate>(rhs));
    return *this;
}
    
template <typename _Return, typename... _Args>
DelegateChain<_Return(_Args...)>& DelegateChain<_Return(_Args...)>::operator-=(const DelegateType& rhs)
{
    auto iter = std::find_if(m_invocationList.begin(), m_invocationList.end(), [&](const DelegateType& item)
    {
        return item == rhs;
    });

    if (iter != m_invocationList.end())
    {
        m_invocationList.erase(iter);
        return true;
    }

    return *this;
}

template <typename _Return, typename... _Args>
DelegateChain<_Return(_Args...)>& DelegateChain<_Return(_Args...)>::operator=(std::nullptr_t rhs) noexcept
{
    m_invocationList.clear();
    return *this;
}

template <typename _Return, typename... _Args>
bool DelegateChain<_Return(_Args...)>::operator==(std::nullptr_t) const noexcept
{
    return m_invocationList.empty();
}

template <typename _Return, typename... _Args>
bool DelegateChain<_Return(_Args...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return !this->operator==(rhs);
}
    
template <typename _Return, typename... _Args>
template <typename... _Args2>
_Return DelegateChain<_Return(_Args...)>::operator()(_Args2&&... args)
{
    return this->Invoke(std::forward<_Args2>(args)...);
}

template <typename _Return, typename... _Args>
template <typename... _Args2>
_Return DelegateChain<_Return(_Args...)>::Invoke(_Args2&&... args)
{
    if (m_invocationList.empty() == true)
    {
        return _Return();
    }

    for (decltype(m_invocationList.size()) i = 0; i < m_invocationList.size() - 1; ++i)
    {
        m_invocationList[i](std::forward<_Args2>(args)...);
    }

    auto iter = m_invocationList.end() - 1;
    return (*iter)(std::forward<_Args2>(args)...);
}

template <typename _Return, typename... _Args>
const std::vector<Delegate<_Return(_Args...)>>& DelegateChain<_Return(_Args...)>::GetInvocationList() const noexcept
{
    return m_invocationList;
}

}
