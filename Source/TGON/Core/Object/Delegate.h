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
#define TGON_MAKE_DELEGATE(...) BOOST_PP_CAT(BOOST_PP_OVERLOAD(TGON_MAKE_DELEGATE_, __VA_ARGS__)(__VA_ARGS__), BOOST_PP_EMPTY())

/**
 * @brief                   Binds delegate with global function or lambda
 * @param [in] function     Insert lambda or reference of global function(e.g. &functionName)
 */
#define TGON_MAKE_DELEGATE_1(function)\
    [&]()\
    {\
        auto instantiatedLambda = function;\
        return tgon::object::Delegate<tgon::utility::FunctionTraits<decltype(instantiatedLambda)>::FunctionTy>::MakeDelegate(function);\
    }()

/**
 * @brief                   Binds delegate with class member function
 * @param [in] function     A Reference of class member function (e.g. &ClassName::functionName)
 * @param [in] instance     A Instance which handles the event
 */
#define TGON_MAKE_DELEGATE_2(function, instance) tgon::object::Delegate<tgon::utility::FunctionTraits<decltype(function)>::FunctionTy>::MakeDelegate<tgon::utility::FunctionTraits<decltype(function)>::ClassTy, function>(instance)

namespace tgon
{
namespace object
{

template <typename Ty>
class Delegate;

template <typename ReturnTy, typename... Args>
class Delegate<ReturnTy(Args...)> final
{
    using Deleter = std::size_t(*)(void*);
    using StubTy = ReturnTy(*)(void*, Args&&...);

/**
 * @section Ctor/Dtor
 */
public:
    constexpr Delegate() noexcept;
    constexpr Delegate(std::nullptr_t) noexcept;
    constexpr Delegate(void* receiver, StubTy stub) noexcept;
    constexpr Delegate(void* receiver, StubTy stub, Deleter deleter) noexcept;
    template <typename FunctionTy>
    Delegate(FunctionTy function);
    Delegate(const Delegate& rhs);
    constexpr Delegate(Delegate&&) noexcept;
    ~Delegate();

/**
 * @section Operator
 */
public:
    Delegate& operator=(const Delegate&);
    Delegate& operator=(Delegate&&);
    constexpr bool operator==(std::nullptr_t) const noexcept;
    constexpr bool operator!=(std::nullptr_t) const noexcept;
    ReturnTy operator()(Args&&...) const;

/**
 * @section Public method
 */
public:
    template <typename FunctionTy>
    static Delegate MakeDelegate(FunctionTy function);

    template <ReturnTy(*Handler)(Args...)>
    static Delegate MakeDelegate() noexcept;
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...)>
    static Delegate MakeDelegate(ClassTy* receiver) noexcept;
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const>
    static Delegate MakeDelegate(ClassTy* receiver) noexcept;
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) volatile>
    static Delegate MakeDelegate(ClassTy* receiver) noexcept;
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const volatile>
    static Delegate MakeDelegate(ClassTy* receiver) noexcept;

/**
 * @section Private method
 */
private:
    template <typename FunctionTy>
    static ReturnTy MakeStub(void* receiver, Args&&... args);
    
    template <ReturnTy(*Handler)(Args...)>
    static ReturnTy MakeStub(void* receiver, Args&&... args);
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...)>
    static ReturnTy MakeStub(void* receiver, Args&&... args);
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const>
    static ReturnTy MakeStub(void* receiver, Args&&... args);
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) volatile>
    static ReturnTy MakeStub(void* receiver, Args&&... args);
    
    template <typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const volatile>
    static ReturnTy MakeStub(void* receiver, Args&&... args);

    /**
     * @brief               The function deletes stored function in m_ptr
     * @param [in]  ptr     Delete target
     * @return              The size to delete, or deleted
     */
    template <typename FunctionTy>
    static std::size_t MakeDeleter(void* ptr);

    static std::size_t GetStoredFunctionSize(Deleter deleter);

/**
 * @section Private variable
 */
private:
    void* m_ptr;
    Deleter m_deleter;
    StubTy m_stub;
};

template<typename ReturnTy, typename... Args>
constexpr Delegate<ReturnTy(Args...)>::Delegate() noexcept :
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
{
}

template<typename ReturnTy, typename ...Args>
constexpr Delegate<ReturnTy(Args...)>::Delegate(std::nullptr_t) noexcept :
#ifdef _MSC_VER
    m_ptr(nullptr),
    m_deleter(nullptr),
    m_stub(nullptr)
#else
    Delegate()
#endif
{
}

template<typename ReturnTy, typename... Args>
constexpr Delegate<ReturnTy(Args...)>::Delegate(void* receiver, StubTy stub) noexcept :
	m_ptr(receiver),
    m_deleter(nullptr),
	m_stub(stub)
{
}

template<typename ReturnTy, typename... Args>
constexpr Delegate<ReturnTy(Args...)>::Delegate(void* receiver, StubTy stub, Deleter deleter) noexcept :
	m_ptr(receiver),
    m_deleter(deleter),
	m_stub(stub)
{
}

template <typename ReturnTy, typename... Args>
template <typename FunctionTy>
inline Delegate<ReturnTy(Args...)>::Delegate(FunctionTy function) :
	m_ptr(operator new(sizeof(FunctionTy))),
    m_stub(&MakeStub<typename std::decay<FunctionTy>::type>),
    m_deleter(&MakeDeleter<typename std::decay<FunctionTy>::type>)
{
    new (m_ptr) typename std::decay<FunctionTy>::type(function);
}

template<typename ReturnTy, typename... Args>
inline Delegate<ReturnTy(Args...)>::Delegate(const Delegate& rhs) :
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

template<typename ReturnTy, typename... Args>
constexpr Delegate<ReturnTy(Args...)>::Delegate(Delegate&& rhs) noexcept :
    m_ptr(rhs.m_ptr),
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    rhs.m_deleter = nullptr;
    rhs.m_ptr = nullptr;
    rhs.m_stub = nullptr;
}

template<typename ReturnTy, typename... Args>
inline Delegate<ReturnTy(Args...)>::~Delegate()
{
    if (m_deleter)
    {
        m_deleter(m_ptr);

        m_deleter = nullptr;
        m_ptr = nullptr;
    }
}

template<typename ReturnTy, typename... Args>
inline Delegate<ReturnTy(Args...)>& Delegate<ReturnTy(Args...)>::operator=(const Delegate& rhs)
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

template<typename ReturnTy, typename... Args>
inline Delegate<ReturnTy(Args...)>& Delegate<ReturnTy(Args...)>::operator=(Delegate&& rhs)
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

template<typename ReturnTy, typename... Args>
inline constexpr bool Delegate<ReturnTy(Args...)>::operator==(std::nullptr_t) const noexcept
{
    return m_stub == nullptr;
}

template<typename ReturnTy, typename... Args>
inline constexpr bool Delegate<ReturnTy(Args...)>::operator!=(std::nullptr_t) const noexcept
{
    return m_stub != nullptr;
}

template<typename ReturnTy, typename... Args>
inline ReturnTy Delegate<ReturnTy(Args...)>::operator()(Args&&... args) const
{
    return m_stub(m_ptr, std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename FunctionTy>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate(FunctionTy function)
{
    return Delegate(function);
}

template<typename ReturnTy, typename... Args>
template<ReturnTy(*Handler)(Args...)>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate() noexcept
{
    return Delegate(nullptr, &MakeStub<Handler>);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...)>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate(ClassTy* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<ClassTy, Handler>);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate(ClassTy* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<ClassTy, Handler>);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) volatile>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate(ClassTy* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<ClassTy, Handler>);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::*Handler)(Args...) const volatile>
inline Delegate<ReturnTy(Args...)> Delegate<ReturnTy(Args...)>::MakeDelegate(ClassTy* receiver) noexcept
{
    return Delegate(receiver, &MakeStub<ClassTy, Handler>);
}

template<typename ReturnTy, typename... Args>
template <typename FunctionTy>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return (*reinterpret_cast<FunctionTy*>(receiver))(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<ReturnTy(*Handler)(Args...)>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return Handler(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::* Handler)(Args...)>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return (reinterpret_cast<ClassTy*>(receiver)->*Handler)(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::* Handler)(Args...) const>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return (reinterpret_cast<ClassTy*>(receiver)->*Handler)(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::* Handler)(Args...) volatile>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return (reinterpret_cast<ClassTy*>(receiver)->*Handler)(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename ClassTy, ReturnTy(ClassTy::* Handler)(Args...) const volatile>
inline ReturnTy Delegate<ReturnTy(Args...)>::MakeStub(void* receiver, Args&&... args)
{
    return (reinterpret_cast<ClassTy*>(receiver)->*Handler)(std::forward<Args>(args)...);
}

template<typename ReturnTy, typename... Args>
template<typename FunctionTy>
inline std::size_t Delegate<ReturnTy(Args...)>::MakeDeleter(void* ptr)
{
    operator delete(ptr);
    return sizeof(FunctionTy);
}

template<typename ReturnTy, typename... Args>
inline std::size_t Delegate<ReturnTy(Args...)>::GetStoredFunctionSize(Deleter deleter)
{
    return (deleter != nullptr) ? deleter(nullptr) : 0;
}

} /* namespace object */
} /* namespace tgon */
