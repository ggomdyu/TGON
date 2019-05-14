/**
 * @file    Delegate.h
 * @author  ggomdyu
 * @since   09/25/2016
 * @seealso https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
 */

#pragma once
#include <type_traits>
#include <cstring>
#include <cstdint>
#include <utility>
#include <new>

#include "TypeTraits.h"

namespace tgon
{

template <typename>
class Delegate;

template <typename _ReturnType, typename... _ArgTypes>
class Delegate<_ReturnType(_ArgTypes...)> final
{
/**@section Type */
private:
    using DeleterType = std::size_t(*)(void*);
    using StubType = _ReturnType(*)(void*, _ArgTypes...);
    
public:
    using ReturnType = _ReturnType;

/**@section Constructor */
public:
    constexpr Delegate() noexcept;
    constexpr Delegate(std::nullptr_t) noexcept;
    constexpr Delegate(void* receiver, StubType stub) noexcept;
    constexpr Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept;
    template <typename _FunctionType>
    Delegate(_FunctionType function);
    Delegate(const Delegate& rhs);
    constexpr Delegate(Delegate&& rhs) noexcept;

/**@section Destructor */
public:
    ~Delegate();

/**@section Operator */
public:
    Delegate& operator=(const Delegate& rhs);
    Delegate& operator=(Delegate&& rhs);
    constexpr bool operator==(std::nullptr_t rhs) const noexcept;
    constexpr bool operator!=(std::nullptr_t rhs) const noexcept;
    constexpr bool operator==(const Delegate& rhs) const noexcept;
    constexpr bool operator!=(const Delegate& rhs) const noexcept;
    template <typename... _ArgTypes2>
    _ReturnType operator()(_ArgTypes2&&... args) const;

/**@section Method */
public:
    template <typename _FunctionType>
    static Delegate MakeDelegate(_FunctionType function);

    template <_ReturnType(*Handler)(_ArgTypes...)>
    static Delegate MakeDelegate() noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...)>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) volatile>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const volatile>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;

private:
    template <typename _FunctionType>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);
    
    template <_ReturnType(*Handler)(_ArgTypes...)>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...)>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) volatile>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const volatile>
    static _ReturnType MakeStub(void* receiver, _ArgTypes... args);

    /**
     * @brief   Deletes the pointer specified by ptr.
     * @param [in]  ptr     The delete target pointer
     * @return  The size to delete or deleted
     */
    template <typename _FunctionType>
    static std::size_t MakeDeleter(void* ptr);

/**@section Variable */
private:
    void* m_ptr;
    DeleterType m_deleter;
    StubType m_stub;
};

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate() noexcept :
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
{
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(std::nullptr_t) noexcept :
    Delegate()
{
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, StubType stub) noexcept :
    m_ptr(receiver),
    m_deleter(nullptr),
    m_stub(stub)
{
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept :
    m_ptr(receiver),
    m_deleter(deleter),
    m_stub(stub)
{
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType function) :
    m_ptr(operator new(sizeof(typename std::decay<_FunctionType>::type))),
    m_stub(&MakeStub<typename std::decay<_FunctionType>::type>),
    m_deleter(&MakeDeleter<typename std::decay<_FunctionType>::type>)
{
    new (m_ptr) typename std::decay<_FunctionType>::type(std::forward<_FunctionType>(function));
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(const Delegate& rhs) :
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    if (m_deleter)
    {
        std::size_t allocationSize = m_deleter(nullptr);

        m_ptr = operator new(allocationSize);
        std::memcpy(m_ptr, rhs.m_ptr, allocationSize);
    }
    else
    {
        m_ptr = nullptr;
    }
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(Delegate&& rhs) noexcept :
    m_ptr(rhs.m_ptr),
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    rhs.m_deleter = nullptr;
    rhs.m_ptr = nullptr;
    rhs.m_stub = nullptr;
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::~Delegate()
{
    if (m_deleter)
    {
        m_deleter(m_ptr);

        m_deleter = nullptr;
        m_ptr = nullptr;
    }
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(const Delegate& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    if (m_deleter)
    {
        m_deleter(m_ptr);
    }

    m_deleter = rhs.m_deleter;
    m_stub = rhs.m_stub;

    if (rhs.m_deleter)
    {
        std::size_t allocationSize = m_deleter(nullptr);

        m_ptr = operator new(allocationSize);
        std::memcpy(m_ptr, rhs.m_ptr, allocationSize);
    }
    else
    {
        m_ptr = nullptr;
    }

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(Delegate&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    if (m_deleter)
    {
        m_deleter(m_ptr);
    }
    
    m_deleter = rhs.m_deleter;
    m_ptr = rhs.m_ptr;
    m_stub = rhs.m_stub;
    
    rhs.m_deleter = nullptr;
    rhs.m_ptr = nullptr;
    rhs.m_stub = nullptr;
    
    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(std::nullptr_t rhs) const noexcept
{
    return m_stub == nullptr;
}

template <typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return m_stub != nullptr;
}

template <typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(const Delegate& rhs) const noexcept
{
    return m_stub == rhs.m_stub;
}

template <typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(const Delegate& rhs) const noexcept
{
    return m_stub != rhs.m_stub;
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename... _ArgTypes2>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::operator()(_ArgTypes2&&... args) const
{
    return m_stub(m_ptr, std::forward<_ArgTypes2>(args)...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_FunctionType function)
{
    return Delegate(std::forward<_FunctionType>(function));
}

template <typename _ReturnType, typename... _ArgTypes>
template <_ReturnType(*Handler)(_ArgTypes...)>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate() noexcept
{
    return Delegate(nullptr, &MakeStub<Handler>);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...)>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) volatile>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const volatile>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return (*reinterpret_cast<_FunctionType*>(receiver))(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <_ReturnType(*Handler)(_ArgTypes...)>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return Handler(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...)>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) const>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) volatile>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) const volatile>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(args...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline std::size_t Delegate<_ReturnType(_ArgTypes...)>::MakeDeleter(void* ptr)
{
    operator delete(ptr);
    return sizeof(_FunctionType);
}
    
template <auto _Function>
auto MakeDelegate(typename FunctionTraits<decltype(_Function)>::ClassType* receiver)
{
    using ClassType = typename FunctionTraits<decltype(_Function)>::ClassType;
    
    return Delegate<typename FunctionTraits<decltype(_Function)>::FunctionType>::template MakeDelegate<ClassType, _Function>(receiver);
}

template <auto _Function>
auto MakeDelegate()
{
    return Delegate<typename FunctionTraits<decltype(_Function)>::FunctionType>::template MakeDelegate<_Function>();
}

template <typename _FunctionType>
auto MakeDelegate(_FunctionType&& function)
{
    return Delegate<typename FunctionTraits<_FunctionType>::FunctionType>(std::forward<_FunctionType>(function));
}

} /* namespace tgon */
