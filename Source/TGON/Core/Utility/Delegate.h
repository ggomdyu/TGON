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
 * @brief   Enable macro overloading for TGON_MAKE_DELEGATE.
 */
#if BOOST_PP_VARIADICS_MSVC
#   define TGON_MAKE_DELEGATE(...) BOOST_PP_CAT(BOOST_PP_OVERLOAD(TGON_MAKE_DELEGATE_, __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())
#else
#   define TGON_MAKE_DELEGATE(...) BOOST_PP_OVERLOAD(TGON_MAKE_DELEGATE_,__VA_ARGS__)(__VA_ARGS__)
#endif

/**
 * @brief                   Binds delegate with lambda or global function
 * @param [in] function     Lambda or Reference of global function(e.g. &functionName)
 */
#define TGON_MAKE_DELEGATE_1(_function)\
    [&]()\
    {\
        auto function = _function;\
        return tgon::utility::Delegate<tgon::utility::FunctionTraits<decltype(function)>::FunctionType>::MakeDelegate(_function);\
    }()

/**
 * @brief                   Binds delegate with class member function
 * @param [in] function     A Reference of class member function(e.g. &ClassName::functionName)
 * @param [in] instance     A Instance which handles event
 */
#define TGON_MAKE_DELEGATE_2(function, instance) tgon::utility::Delegate<tgon::utility::FunctionTraits<decltype(function)>::FunctionType>::MakeDelegate<tgon::utility::FunctionTraits<decltype(function)>::ClassType, function>(instance)

namespace tgon
{
namespace utility
{

template <typename>
class Delegate;

template <typename _ReturnType, typename... _ArgTypes>
class Delegate<_ReturnType(_ArgTypes...)> final
{
    using DeleterType = std::size_t(*)(void*);
    using StubType = _ReturnType(*)(void*, _ArgTypes&&...);

/* @section Public constructor */
public:
    constexpr Delegate() noexcept;
    constexpr Delegate(std::nullptr_t) noexcept;
    constexpr Delegate(void* receiver, StubType stub) noexcept;
    constexpr Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept;
    template <typename _FunctionType>
    Delegate(_FunctionType&& function);
    Delegate(const Delegate& rhs);
    constexpr Delegate(Delegate&&) noexcept;

/* @section Public destructor */
public:
    ~Delegate();

/* @section Public operator */
public:
    Delegate& operator=(const Delegate&);
    Delegate& operator=(Delegate&&);
    constexpr bool operator==(std::nullptr_t) const noexcept;
    constexpr bool operator!=(std::nullptr_t) const noexcept;
    _ReturnType operator()(_ArgTypes&&...) const;

/* @section Public method */
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

/* @section Private method */
private:
    template <typename _FunctionType>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);
    
    template <_ReturnType(*Handler)(_ArgTypes...)>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...)>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) volatile>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);
    
    template <typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const volatile>
    static _ReturnType MakeStub(void* receiver, _ArgTypes&&... args);

    /**
     * @brief               Deletes function stored in m_ptr
     * @param [in]  ptr     Delete target
     * @return              The size to delete, or deleted
     */
    template <typename _FunctionType>
    static std::size_t MakeDeleter(void* ptr);

    static std::size_t GetStoredFunctionSize(DeleterType deleter);

/* @section Private variable */
private:
    void* m_ptr;
    DeleterType m_deleter;
    StubType m_stub;
};

template<typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate() noexcept :
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
{
}

template<typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(std::nullptr_t) noexcept :
#ifdef _MSC_VER
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
#else
    Delegate()
#endif
{
}

template<typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, StubType stub) noexcept :
	m_ptr(receiver),
    m_deleter(nullptr),
	m_stub(stub)
{
}

template<typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, StubType stub, DeleterType deleter) noexcept :
	m_ptr(receiver),
    m_deleter(deleter),
	m_stub(stub)
{
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType&& function) :
	m_ptr(operator new(sizeof(typename std::decay<_FunctionType>::type))),
    m_stub(&MakeStub<typename std::decay<_FunctionType>::type>),
    m_deleter(&MakeDeleter<typename std::decay<_FunctionType>::type>)
{
    new (m_ptr) typename std::decay<_FunctionType>::type(std::forward<_FunctionType>(function));
}

template<typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(const Delegate& rhs) :
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

template<typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(Delegate&& rhs) noexcept :
    m_ptr(rhs.m_ptr),
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    rhs.m_deleter = nullptr;
    rhs.m_ptr = nullptr;
    rhs.m_stub = nullptr;
}

template<typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::~Delegate()
{
    if (m_deleter)
    {
        m_deleter(m_ptr);

        m_deleter = nullptr;
        m_ptr = nullptr;
    }
}

template<typename _ReturnType, typename... _ArgTypes>
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

template<typename _ReturnType, typename... _ArgTypes>
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

template<typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(std::nullptr_t) const noexcept
{
    return m_stub == nullptr;
}

template<typename _ReturnType, typename... _ArgTypes>
inline constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(std::nullptr_t) const noexcept
{
    return m_stub != nullptr;
}

template<typename _ReturnType, typename... _ArgTypes>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::operator()(_ArgTypes&&... args) const
{
    return m_stub(m_ptr, std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_FunctionType function)
{
    return Delegate(function);
}

template<typename _ReturnType, typename... _ArgTypes>
template<_ReturnType(*Handler)(_ArgTypes...)>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate() noexcept
{
    return Delegate(nullptr, &MakeStub<Handler>);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...)>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) volatile>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::*Handler)(_ArgTypes...) const volatile>
inline Delegate<_ReturnType(_ArgTypes...)> Delegate<_ReturnType(_ArgTypes...)>::MakeDelegate(_ClassType* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<_ClassType, Handler>);
}

template<typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return (*reinterpret_cast<_FunctionType*>(receiver))(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<_ReturnType(*Handler)(_ArgTypes...)>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return Handler(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...)>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) const>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) volatile>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _ClassType, _ReturnType(_ClassType::* Handler)(_ArgTypes...) const volatile>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::MakeStub(void* receiver, _ArgTypes&&... args)
{
    return (reinterpret_cast<_ClassType*>(receiver)->*Handler)(std::forward<_ArgTypes>(args)...);
}

template<typename _ReturnType, typename... _ArgTypes>
template<typename _FunctionType>
inline std::size_t Delegate<_ReturnType(_ArgTypes...)>::MakeDeleter(void* ptr)
{
    operator delete(ptr);
    return sizeof(_FunctionType);
}

template<typename _ReturnType, typename... _ArgTypes>
inline std::size_t Delegate<_ReturnType(_ArgTypes...)>::GetStoredFunctionSize(DeleterType deleter)
{
    return (deleter != nullptr) ? deleter(nullptr) : 0;
}

} /* namespace utility */
} /* namespace tgon */
