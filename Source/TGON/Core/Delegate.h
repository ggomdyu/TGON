/**
 * @file    Delegate.h
 * @author  ggomdyu
 * @since   09/25/2016
 * @seealso https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
 */

#pragma once
#include <type_traits>
#include <array>

#include "TypeTraits.h"

namespace tgon
{
namespace experimental
{
namespace detail
{

template <typename _ReturnType, typename... _ArgTypes>
class Callable
{
/**@section Destructor */
public:
    virtual ~Callable() = default;

/**@section Method */
public:
    virtual void CopyTo(Callable** callable) const = 0;
    virtual _ReturnType Invoke(_ArgTypes... args) const = 0;
    virtual void Destroy() = 0;
};

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
class CallableImpl :
    public Callable<_ReturnType, _ArgTypes...>
{
/**@section Constructor */
public:
    explicit CallableImpl(_FunctionType function, void* receiver = nullptr) noexcept;
    
/**@section Method */
public:
    void CopyTo(Callable<_ReturnType, _ArgTypes...>** callable) const override;
    _ReturnType Invoke(_ArgTypes... args) const override;
    void Destroy() override;

/**@section Variable */
private:
    _FunctionType m_function;
    void* m_receiver;
};

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline CallableImpl<_FunctionType, _ReturnType, _ArgTypes...>::CallableImpl(_FunctionType function, void* receiver) noexcept :
    m_function(function),
    m_receiver(receiver)
{
}

template<typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline void CallableImpl<_FunctionType, _ReturnType, _ArgTypes...>::CopyTo(Callable<_ReturnType, _ArgTypes...>** callable) const
{
    Callable<_ReturnType, _ArgTypes...>* lhs = *callable;
    new (&*callable) CallableImpl<_FunctionType, _ReturnType, _ArgTypes...>(m_function, m_receiver);
}

template<typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline _ReturnType CallableImpl<_FunctionType, _ReturnType, _ArgTypes...>::Invoke(_ArgTypes... args) const
{
    if constexpr (tgon::FunctionTraits<_FunctionType>::IsMemberFunction)
    {
        return (reinterpret_cast<typename tgon::FunctionTraits<_FunctionType>::ClassType*>(m_receiver)->*m_function)(args...);
    }
    else
    {
        return m_function(args...);
    }
}

template<typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline void CallableImpl<_FunctionType, _ReturnType, _ArgTypes...>::Destroy()
{
    if constexpr (tgon::FunctionTraits<_FunctionType>::IsFunctor)
    {
        m_function.~_FunctionType();
    }
}

} /* namespace detail */

template <typename>
class Delegate;

template <typename _ReturnType, typename... _ArgTypes>
class Delegate<_ReturnType(_ArgTypes...)> final
{
/**@section Type */
public:
    using ReturnType = _ReturnType;

private:
    template <typename _FunctionType>
    using CallableImpl = detail::CallableImpl<std::decay_t<_FunctionType>, _ReturnType, _ArgTypes...>;
    using Callable = detail::Callable<_ReturnType, _ArgTypes...>;

/**@section Constructor */
public:
    constexpr Delegate() noexcept = default;
    constexpr Delegate(std::nullptr_t) noexcept;
    Delegate(const Delegate& rhs);
    Delegate(Delegate&& rhs) noexcept;
    template <typename _FunctionType>
    Delegate(_FunctionType function, void* receiver = nullptr);

/**@section Destructor */
public:
    ~Delegate();

/**@section Operator */
public:
    template <typename... _ArgTypes2>
    _ReturnType operator()(_ArgTypes2&&... args) const;
    Delegate& operator=(const Delegate& rhs);
    Delegate& operator=(Delegate&& rhs) noexcept;
    constexpr bool operator==(std::nullptr_t rhs) const noexcept;
    constexpr bool operator!=(std::nullptr_t rhs) const noexcept;
    constexpr bool operator==(const Delegate& rhs) const noexcept;
    constexpr bool operator!=(const Delegate& rhs) const noexcept;

/**@section Method */
private:
    Callable* GetCallable();
    const Callable* GetCallable() const;

/**@section Variable */
private:
    union
    {
        std::array<char, sizeof(void*) * 8> m_dummy{};
        Callable* m_callable;
    };
};

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(std::nullptr_t) noexcept :
    Delegate()
{
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(const Delegate& rhs) :
    m_callable(nullptr)
{
    rhs.GetCallable()->CopyTo(&m_callable);
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(Delegate&& rhs) noexcept :
    m_dummy(rhs.m_dummy)
{
    rhs.m_callable = nullptr;
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType function, void* receiver)
{
    new (&m_callable) CallableImpl<_FunctionType>(function, receiver);
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::~Delegate()
{
    if (m_callable)
    {
        this->GetCallable()->Destroy();
        m_callable = nullptr;
    }
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename... _ArgTypes2>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::operator()(_ArgTypes2&&... args) const
{
    if (m_callable == nullptr)
    {
        return _ReturnType();
    }

    return this->GetCallable()->Invoke();
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(const Delegate& rhs)
{
    rhs.GetCallable()->CopyTo(&m_callable);

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(Delegate&& rhs) noexcept
{
    m_callable = rhs.m_callable;
    rhs.m_callable = nullptr;

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(std::nullptr_t rhs) const noexcept
{
    return m_callable == rhs;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return m_callable != rhs;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(const Delegate& rhs) const noexcept
{
    return m_callable == rhs.m_callable;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(const Delegate& rhs) const noexcept
{
    return m_callable != rhs.m_callable;
}

template <typename _ReturnType, typename... _ArgTypes>
inline detail::Callable<_ReturnType, _ArgTypes...>* Delegate<_ReturnType(_ArgTypes...)>::GetCallable()
{
    return reinterpret_cast<Callable*>(&m_callable);
}

template <typename _ReturnType, typename... _ArgTypes>
inline const detail::Callable<_ReturnType, _ArgTypes...>* Delegate<_ReturnType(_ArgTypes...)>::GetCallable() const
{
    return reinterpret_cast<const Callable*>(&m_callable);
}

} /* namespace experimental */

template <typename>
class Delegate;

template <typename _ReturnType, typename... _ArgTypes>
class Delegate<_ReturnType(_ArgTypes...)> final
{
/**@section Type */
private:
    using Deleter = size_t(*)(void*);
    using Stub = _ReturnType(*)(void*, _ArgTypes...);
    
public:
    using ReturnType = _ReturnType;

/**@section Constructor */
public:
    constexpr Delegate() noexcept;
    constexpr Delegate(std::nullptr_t) noexcept;
    constexpr Delegate(void* receiver, Stub stub) noexcept;
    constexpr Delegate(void* receiver, Stub stub, Deleter deleter) noexcept;
    template <typename _FunctionType>
    Delegate(_FunctionType function);
    Delegate(const Delegate& rhs);
    constexpr Delegate(Delegate&& rhs) noexcept;

/**@section Destructor */
public:
    ~Delegate();

/**@section Operator */
public:
    template <typename... _ArgTypes2>
    _ReturnType operator()(_ArgTypes2&&... args) const;
    Delegate& operator=(const Delegate& rhs);
    Delegate& operator=(Delegate&& rhs) noexcept;
    constexpr bool operator==(std::nullptr_t rhs) const noexcept;
    constexpr bool operator!=(std::nullptr_t rhs) const noexcept;
    constexpr bool operator==(const Delegate& rhs) const noexcept;
    constexpr bool operator!=(const Delegate& rhs) const noexcept;

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
    template <typename _FunctionType>
    static size_t MakeDeleter(void* ptr);

/**@section Variable */
private:
    void* m_ptr;
    Deleter m_deleter;
    Stub m_stub;
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
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, Stub stub) noexcept :
    m_ptr(receiver),
    m_deleter(nullptr),
    m_stub(stub)
{
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(void* receiver, Stub stub, Deleter deleter) noexcept :
    m_ptr(receiver),
    m_deleter(deleter),
    m_stub(stub)
{
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType function) :
    m_ptr(operator new(sizeof(std::decay_t<_FunctionType>))),
    m_stub(&MakeStub<std::decay_t<_FunctionType>>),
    m_deleter(&MakeDeleter<std::decay_t<_FunctionType>>)
{
    new (m_ptr) std::decay_t<_FunctionType>(function);
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(const Delegate& rhs) :
    m_deleter(rhs.m_deleter),
    m_stub(rhs.m_stub)
{
    if (m_deleter)
    {
        size_t allocationSize = m_deleter(nullptr);

        m_ptr = operator new(allocationSize);
        memcpy(m_ptr, rhs.m_ptr, allocationSize);
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
        size_t allocationSize = m_deleter(nullptr);

        m_ptr = operator new(allocationSize);
        memcpy(m_ptr, rhs.m_ptr, allocationSize);
    }
    else
    {
        m_ptr = nullptr;
    }

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(Delegate&& rhs) noexcept
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
inline size_t Delegate<_ReturnType(_ArgTypes...)>::MakeDeleter(void* ptr)
{
    operator delete(ptr);
    return sizeof(_FunctionType);
}
    
template <auto Function>
auto MakeDelegate(typename FunctionTraits<decltype(Function)>::ClassType* receiver)
{
    using ClassType = typename FunctionTraits<decltype(Function)>::ClassType;
    
    return Delegate<typename FunctionTraits<decltype(Function)>::FunctionType>::template MakeDelegate<ClassType, Function>(receiver);
}

template <auto Function>
auto MakeDelegate()
{
    return Delegate<typename FunctionTraits<decltype(Function)>::FunctionType>::template MakeDelegate<Function>();
}

template <typename _FunctionType>
auto MakeDelegate(_FunctionType&& function)
{
    return Delegate<typename FunctionTraits<_FunctionType>::FunctionType>(std::forward<_FunctionType>(function));
}

} /* namespace tgon */
