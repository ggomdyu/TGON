/**
 * filename TDelegateChain.h
 * author   ggomdyu
 * since    04/01/2017
 */

#pragma once
#include <vector>
#include <iterator>

#include "TDelegate.h"

namespace tgon
{

template <typename>
struct TDelegateChain;

template <typename ReturnTy, typename... Args>
struct TDelegateChain<ReturnTy(Args...)> :
    private std::vector<TDelegate<ReturnTy(Args...)>>
{
public:
    using DelegateTy = TDelegate<ReturnTy(Args...)>;
    using SuperTy = std::vector<DelegateTy>;

    using allocator_type = typename SuperTy::allocator_type;
    using value_type = typename SuperTy::value_type;
    using size_type = typename SuperTy::size_type;
    using difference_type = typename SuperTy::difference_type;
    using pointer = typename SuperTy::pointer;
    using const_pointer = typename SuperTy::const_pointer;
    using reference = typename SuperTy::reference;
    using const_reference = typename SuperTy::const_reference;
    using reverse_iterator = typename SuperTy::reverse_iterator;
    using const_reverse_iterator = typename SuperTy::const_reverse_iterator;

/**
 * @section Ctor/Dtor
 */
public:
    using SuperTy::SuperTy;

/**
 * @section Operator
 */
public:
    using SuperTy::operator[];
    using SuperTy::operator=;

    void operator()(Args&&... args);

    TDelegateChain& operator+=(const DelegateTy& rhs);
    TDelegateChain& operator+=(DelegateTy&& rhs);
    TDelegateChain& operator+=(const TDelegateChain& rhs);
    TDelegateChain& operator+=(TDelegateChain&& rhs);
    TDelegateChain operator+(const TDelegateChain& rhs) const;
    TDelegateChain operator+(TDelegateChain&& rhs) const;

/**
 * @section Public methods
 */
public:
    using SuperTy::insert;
    using SuperTy::assign;
    using SuperTy::reserve;
    using SuperTy::capacity;
    using SuperTy::begin;
    using SuperTy::end;
    using SuperTy::rbegin;
    using SuperTy::rend;
    using SuperTy::cbegin;
    using SuperTy::cend;
    using SuperTy::crbegin;
    using SuperTy::crend;
    using SuperTy::resize;
    using SuperTy::size;
    using SuperTy::max_size;
    using SuperTy::empty;
    using SuperTy::get_allocator;
    using SuperTy::at;
    using SuperTy::data;
    using SuperTy::front;
    using SuperTy::back;
    using SuperTy::emplace_back;
    using SuperTy::push_back;
    using SuperTy::pop_back;
    using SuperTy::erase;
    using SuperTy::clear;
    using SuperTy::swap;
};

template<typename ReturnTy, typename ...Args>
inline void TDelegateChain<ReturnTy(Args...)>::operator()(Args&& ...args)
{
    for (auto& elem : *this)
    {
        elem(std::forward<Args>(args)...);
    }
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)>& TDelegateChain<ReturnTy(Args...)>::operator+=(const DelegateTy& rhs)
{
    SuperTy::push_back(rhs);
    return *this;
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)>& TDelegateChain<ReturnTy(Args...)>::operator+=(DelegateTy&& rhs)
{
    SuperTy::push_back(std::move(rhs));
    return *this;
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)>& TDelegateChain<ReturnTy(Args...)>::operator+=(const TDelegateChain& rhs)
{
    this->reserve(this->size() + rhs.size());
    this->insert(this->end(), rhs.begin(), rhs.end());

    return *this;
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)>& TDelegateChain<ReturnTy(Args...)>::operator+=(TDelegateChain&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    this->reserve(this->size() + rhs.size());
    std::move(rhs.begin(), rhs.end(), std::back_inserter(*this));
    rhs.clear();

    return *this;
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)> TDelegateChain<ReturnTy(Args...)>::operator+(const TDelegateChain& rhs) const
{
    TDelegateChain ret;
    ret.reserve(this->size() + rhs.size());
    ret.insert(ret.end(), this->begin(), this->end());
    ret.insert(ret.end(), rhs.begin(), rhs.end());

    return ret;
}

template<typename ReturnTy, typename ...Args>
inline TDelegateChain<ReturnTy(Args...)> TDelegateChain<ReturnTy(Args...)>::operator+(TDelegateChain&& rhs) const
{
    if (this == &rhs)
    {
        return *this;
    }

    TDelegateChain ret;
    ret.reserve(this->size() + rhs.size());
    ret.insert(ret.end(), this->begin(), this->end());
    std::move(rhs.begin(), rhs.end(), std::back_inserter(ret));
    rhs.clear();

    return ret;
}

}