/**
 * @filename    Delegate.h
 * @author      ggomdyu
 * @since       09/25/2016
 * @see         https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
 */

#pragma once
#include <type_traits>
#include <cstring>
#include <cstdint>
#include <utility>
#include <new>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include "Core/Utility/TypeTraits.h"

/**
 * @see     http://www.boost.org/doc/libs/master/libs/preprocessor/doc/ref/overload.html
 * @brief   Overloaded delegate macros
 */
#if BOOST_PP_VARIADICS_MSVC
#   define TGON_MAKE_DELEGATE(...) BOOST_PP_CAT(BOOST_PP_OVERLOAD(TGON_MAKE_DELEGATE_, __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())
#else
#   define TGON_MAKE_DELEGATE(...) BOOST_PP_OVERLOAD(TGON_MAKE_DELEGATE_,__VA_ARGS__)(__VA_ARGS__)
#endif

/**
 * @brief                   Binds delegate with global function or lambda
 * @param [in] function     Insert lambda or reference of global function(e.g. &functionName)
 */
#define TGON_MAKE_DELEGATE_1(function)\
    [&]()\
    {\
        auto lValueFunction = function;\
        return tgon::utility::Delegate<tgon::utility::FunctionTraits<decltype(lValueFunction)>::FunctionType>::MakeDelegate(function);\
    }()

/**
 * @brief                   Binds delegate with class member function
 * @param [in] function     A Reference of class member function(e.g. &ClassName::functionName)
 * @param [in] instance     A Instance which handles the event
 */
#define TGON_MAKE_DELEGATE_2(function, instance) tgon::utility::Delegate<tgon::utility::FunctionTraits<decltype(function)>::FunctionType>::MakeDelegate<tgon::utility::FunctionTraits<decltype(function)>::ClassType, function>(instance)

namespace tgon
{
namespace utility
{

template <typename>
class Delegate;

template <typename _ReturnType, typename... _Args>
class Delegate<_ReturnType(_Args...)> final
{
    using DeleterType = std::size_t(*)(void*);
    using StubType = _ReturnType(*)(void*, _Args&&...);

/* @section Ctor/Dtor */
public:
    constexpr Delegate() noexcept;
    constexpr Delegate(std::nullptr_t) noexcept;
    constexpr Delegate(void* receiver, StubType stub) noexcept;
    constexpr Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept;
    template <typename _FunctionType>
    Delegate(_FunctionType&& function);
    Delegate(const Delegate& rhs);
    constexpr Delegate(Delegate&&) noexcept;
    ~Delegate();

/* @section Operator */
public:
    Delegate& operator=(const Delegate&);
    Delegate& operator=(Delegate&&);
    constexpr bool operator==(std::nullptr_t) const noexcept;
    constexpr bool operator!=(std::nullptr_t) const noexcept;
    _ReturnType operator()(_Args&&...) const;

/* @section Public method */
public:
    template <typename _FunctionType>
    static Delegate MakeDelegate(_FunctionType function);

    template <_ReturnType(*Handler)(_Args...)>
    static Delegate MakeDelegate() noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...)>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) volatile>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const volatile>
    static Delegate MakeDelegate(_ClassType* receiver) noexcept;

/* @section Private method */
private:
    template <typename _FunctionType>
    static _ReturnType Stub(void* receiver, _Args&&... args);
    
    template <_ReturnType(*Handler)(_Args...)>
    static _ReturnType Stub(void* receiver, _Args&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...)>
    static _ReturnType Stub(void* receiver, _Args&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const>
    static _ReturnType Stub(void* receiver, _Args&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) volatile>
    static _ReturnType Stub(void* receiver, _Args&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const volatile>
    static _ReturnType Stub(void* receiver, _Args&&... args);

    /**
     * @brief               Deletes function stored in m_ptr
     * @param [in]  ptr     Delete target
     * @return              The size to delete, or deleted
     */
    template <typename _FunctionType>
    static std::size_t Deleter(void* ptr);

    static std::size_t GetStoredFunctionSize(DeleterType deleter);

/* @section Private variable */
private:
    void* m_ptr;
    DeleterType m_deleter;
    StubType m_stub;
};

template<typename _ReturnType, typename... _Args>
constexpr Delegate<_ReturnType(_Args...)>::Delegate() noexcept :
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
{
}

template<typename _ReturnType, typename... _Args>
constexpr Delegate<_ReturnType(_Args...)>::Delegate(std::nullptr_t) noexcept :
#ifdef _MSC_VER
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
#else
    Delegate()
#endif
{
}

template<typename _ReturnType, typename... _Args>
constexpr Delegate<_ReturnType(_Args...)>::Delegate(void* receiver, StubType stub) noexcept :
	m_ptr(receiver),
    m_deleter(nullptr),
	m_stub(stub)
{
}

template<typename _ReturnType, typename... _Args>
constexpr Delegate<_ReturnType(_Args...)>::Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept :
	m_ptr(receiver),
    m_deleter(deleter),
	m_stub(stub)
{
}

template <typename _ReturnType, typename... _Args>
template <typename _FunctionType>
inline Delegate<_ReturnType(_Args...)>::Delegate(_FunctionType&& function) :
	m_ptr(operator new(sizeof(_FunctionType))),
    m_stub(&Stub<typename std::decay<_FunctionType>::type>),
    m_deleter(&Deleter<typename std::decay<_FunctionType>::type>)
{
    new (m_ptr) typename std::decay<_FunctionType>::type(std::forward<_FunctionType>(function));
}

template<typename _ReturnType, typename... _Args>
inline Delegate<_ReturnType(_Args...)>::Delegate(const Delegate& rhs) :
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    if (m_deleter)
    {
        int allocationSize = GetStoredFunctionSize(m_deleter);

        m_ptr = operator new(allocationSize);
        std::memcpy(m_ptr, rhs.m_ptr, allocationSize);
    }
    else
    {
        m_ptr = nullptr;
    }
}

template<typename _ReturnType, typename... _Args>
constexpr Delegate<_ReturnType(_Args...)>::Delegate(Delegate&& rhs) noexcept :
    m_ptr(rhs.m_ptr),
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    rhs.m_deleter = nullptr;
    rhs.m_ptr = nullptr;
    rhs.m_stub = nullptr;
}

template<typename _ReturnType, typename... _Args>
inline Delegate<_ReturnType(_Args...)>::~Delegate()
{
    if (m_deleter)
    {
        m_deleter(m_ptr);

        m_deleter = nullptr;
        m_ptr = nullptr;
    }
}

template<typename _ReturnType, typename... _Args>
inline Delegate<_ReturnType(_Args...)>& Delegate<_ReturnType(_Args...)>::operator=(const Delegate& rhs)
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
        int allocationSize = GetStoredFunctionSize(rhs.m_deleter);

        m_ptr = operator new(allocationSize);
        std::memcpy(m_ptr, rhs.m_ptr, allocationSize);
    }
    else
    {
        m_ptr = nullptr;
    }

    return *this;
}

template<typename _ReturnType, typename... _Args>
inline Delegate<_ReturnType(_Args...)>& Delegate<_ReturnType(_Args...)>::operator=(Delegate&& rhs)
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

template<typename _ReturnType, typename... _Args>
inline constexpr bool Delegate<_ReturnType(_Args...)>::operator==(std::nullptr_t) const noexcept
{
    return m_stub == nullptr;
}

template<typename _ReturnType, typename... _Args>
inline constexpr bool Delegate<_ReturnType(_Args...)>::operator!=(std::nullptr_t) const noexcept
{
    return m_stub != nullptr;
}

template<typename _ReturnType, typename... _Args>
inline _ReturnType Delegate<_ReturnType(_Args...)>::operator()(_Args&&... args) const
{
    return m_stub(m_ptr, std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _FunctionType>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate(_FunctionType function)
{
    return Delegate(function);
}

template<typename _ReturnType, typename... _Args>
template<_ReturnType(*Handler)(_Args...)>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate() noexcept
{
    return Delegate(nullptr, &Stub<Handler>);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...)>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &Stub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &Stub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) volatile>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &Stub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_Args...) const volatile>
inline Delegate<_ReturnType(_Args...)> Delegate<_ReturnType(_Args...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &Stub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _Args>
template <typename _FunctionType>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return (*reinterpret_cast<_FunctionType*>(receiver))(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<_ReturnType(*Handler)(_Args...)>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return Handler(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_Args...)>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_Args...) const>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_Args...) volatile>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_Args...) const volatile>
inline _ReturnType Delegate<_ReturnType(_Args...)>::Stub(void* receiver, _Args&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_Args>(args)...);
}

template<typename _ReturnType, typename... _Args>
template<typename _FunctionType>
inline std::size_t Delegate<_ReturnType(_Args...)>::Deleter(void* ptr)
{
    operator delete(ptr);
    return sizeof(_FunctionType);
}

template<typename _ReturnType, typename... _Args>
inline std::size_t Delegate<_ReturnType(_Args...)>::GetStoredFunctionSize(DeleterType deleter)
{
    return (deleter != nullptr) ? deleter(nullptr) : 0;
}

} /* namespace utility */
} /* namespace tgon */
