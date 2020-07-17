#pragma once

#include <type_traits>
#include <array>

#include "TypeTraits.h"

namespace tg
{

template <typename>
class Delegate;

namespace detail
{

template <typename>
struct IsDelegate : std::false_type {};

template <typename _Type>
struct IsDelegate<Delegate<_Type>> : std::true_type {};

template <typename _Return, typename... _Args>
class Functor
{
/**@section Constructor */
public:
    Functor() = default;
    Functor(const Functor& rhs) = delete;
    Functor(Functor&& rhs) = delete;

/**@section Destructor */
public:
    virtual ~Functor() = default;

/**@section Operator */
public:
    Functor& operator=(const Functor& rhs) = delete;
    Functor& operator=(Functor&& rhs) = delete;

/**@section Method */
public:
    virtual _Return Invoke(_Args... args) const = 0;
    virtual void CopyTo(Functor* functor) const = 0;
    virtual void Destroy() = 0;
    [[nodiscard]] virtual size_t GetSize() const noexcept = 0;
};

template <typename _Function, typename _Return, typename... _Args>
class FunctorImpl final :
    public Functor<_Return, _Args...>
{
/**@section Type */
public:
    using Storage = std::conditional_t<FunctionTraits<_Function>::IsMemberFunction,
        std::tuple<_Function, void*>,
        std::tuple<_Function>
    >;
    
/**@section Constructor */
public:
    explicit FunctorImpl(Storage storage) noexcept;
    
/**@section Method */
public:
    _Return Invoke(_Args... args) const override;
    void CopyTo(Functor<_Return, _Args...>* functor) const override;
    void Destroy() override;
    [[nodiscard]] size_t GetSize() const noexcept override;

/**@section Variable */
private:
    Storage m_storage;
};

template <typename _Function, typename _Return, typename... _Args>
FunctorImpl<_Function, _Return, _Args...>::FunctorImpl(Storage storage) noexcept :
    m_storage(std::move(storage))
{
}

template <typename _Function, typename _Return, typename... _Args>
void FunctorImpl<_Function, _Return, _Args...>::CopyTo(Functor<_Return, _Args...>* functor) const
{
    new (functor) FunctorImpl<_Function, _Return, _Args...>(m_storage);
}

template <typename _Function, typename _Return, typename... _Args>
_Return FunctorImpl<_Function, _Return, _Args...>::Invoke(_Args... args) const
{
    if constexpr (FunctionTraits<_Function>::IsMemberFunction)
    {
        auto& [function, receiver] = m_storage;
        return (reinterpret_cast<typename FunctionTraits<_Function>::ClassType*>(receiver)->*(function))(std::move(args)...);
    }
    else
    {
        return std::get<0>(m_storage)(std::move(args)...);
    }
}

template <typename _Function, typename _Return, typename... _Args>
void FunctorImpl<_Function, _Return, _Args...>::Destroy()
{
    if constexpr (FunctionTraits<_Function>::IsFunctor)
    {
        std::get<0>(m_storage).~_Function();
    }
}

template <typename _Function, typename _Return, typename... _Args>
size_t FunctorImpl<_Function, _Return, _Args...>::GetSize() const noexcept
{
    return sizeof(*this);
}

}

template <typename _Type>
constexpr bool IsDelegate = detail::IsDelegate<_Type>::value;

template <typename _Return, typename... _Args>
class Delegate<_Return(_Args...)> final
{
/**@section Type */
public:
    using ReturnType = _Return;

private:
    template <typename _Function>
    using FunctorImpl = detail::FunctorImpl<_Function, _Return, _Args...>;
    using Functor = detail::Functor<_Return, _Args...>;

/**@section Constructor */
public:
    constexpr Delegate() noexcept = default;
    constexpr Delegate(std::nullptr_t) noexcept;
    Delegate(const Delegate& rhs);
    Delegate(Delegate&& rhs) noexcept;
    template <typename _Function>
    Delegate(_Function function);
    template <typename _Function>
    Delegate(_Function function, void* receiver);

/**@section Destructor */
public:
    ~Delegate();

/**@section Operator */
public:
    template <typename... _Args2>
    _Return operator()(_Args2&&... args) const;
    Delegate& operator=(const Delegate& rhs);
    Delegate& operator=(Delegate&& rhs) noexcept;
    constexpr bool operator==(std::nullptr_t rhs) const noexcept;
    constexpr bool operator!=(std::nullptr_t rhs) const noexcept;

/**@section Method */
private:
    template <typename _Function>
    [[nodiscard]] static constexpr bool IsLargeFunction() noexcept;
    [[nodiscard]] bool IsDynamicAllocated() const noexcept;
    void Destroy();

/**@section Variable */
private:
    static constexpr size_t StorageCapacity = 7;

    Functor* m_functor = nullptr;
    std::array<void*, StorageCapacity> m_storage = {};
};

template <typename _Function>
Delegate(_Function function) -> Delegate<typename FunctionTraits<std::remove_cvref_t<_Function>>::FunctionType>;

template <typename _Function>
Delegate(_Function function, void* receiver) -> Delegate<typename FunctionTraits<std::remove_cvref_t<_Function>>::FunctionType>;

template <typename _Return, typename... _Args>
constexpr Delegate<_Return(_Args...)>::Delegate(std::nullptr_t) noexcept :
    Delegate()
{
}

template <typename _Return, typename... _Args>
Delegate<_Return(_Args...)>::Delegate(const Delegate& rhs) :
    Delegate()
{
    if (rhs.m_functor == nullptr)
    {
        return;
    }

    m_functor = static_cast<Functor*>(rhs.IsDynamicAllocated() ? operator new(rhs.m_functor->GetSize()) : &m_storage[0]);

    rhs.m_functor->CopyTo(m_functor);
}

template <typename _Return, typename... _Args>
Delegate<_Return(_Args...)>::Delegate(Delegate&& rhs) noexcept :
    Delegate()
{
    if (rhs.IsDynamicAllocated())
    {
        m_functor = rhs.m_functor;
    }
    else
    {
        m_storage = rhs.m_storage;
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    rhs.m_functor = nullptr;
}

template <typename _Return, typename... _Args>
template <typename _Function>
Delegate<_Return(_Args...)>::Delegate(_Function function) :
    Delegate()
{
    using FunctionType = std::decay_t<_Function>;
    if constexpr (Delegate::template IsLargeFunction<FunctionType>())
    {
        m_functor = static_cast<Functor*>(operator new(sizeof(FunctorImpl<FunctionType>)));
    }
    else
    {
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    new (m_functor) FunctorImpl<FunctionType>(typename FunctorImpl<FunctionType>::Storage{std::move(function)});
}

template <typename _Return, typename... _Args>
template <typename _Function>
Delegate<_Return(_Args...)>::Delegate(_Function function, void* receiver) :
    Delegate()
{
    using FunctionType = std::decay_t<_Function>;
    if constexpr (Delegate::template IsLargeFunction<FunctionType>())
    {
        m_functor = static_cast<Functor*>(operator new(sizeof(FunctorImpl<FunctionType>)));
    }
    else
    {
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    new (m_functor) FunctorImpl<FunctionType>(typename FunctorImpl<FunctionType>::Storage{std::move(function), receiver});
}

template <typename _Return, typename... _Args>
Delegate<_Return(_Args...)>::~Delegate()
{
    this->Destroy();
}

template <typename _Return, typename... _Args>
template <typename... _Args2>
_Return Delegate<_Return(_Args...)>::operator()(_Args2&&... args) const
{
    if (m_functor == nullptr)
    {
        return _Return();
    }

    return m_functor->Invoke(std::forward<_Args2>(args)...);
}

template <typename _Return, typename... _Args>
template <typename _Function>
constexpr bool Delegate<_Return(_Args...)>::IsLargeFunction() noexcept
{
    return sizeof(FunctorImpl<_Function>) > (sizeof(m_storage) - sizeof(m_storage[0]));
}

template <typename _Return, typename... _Args>
Delegate<_Return(_Args...)>& Delegate<_Return(_Args...)>::operator=(const Delegate& rhs)
{
    this->Destroy();

    if (rhs.m_functor == nullptr)
    {
        return *this;
    }

    m_functor = static_cast<Functor*>(rhs.IsDynamicAllocated() ? operator new(rhs.m_functor->GetSize()) : &m_storage[0]);

    rhs.m_functor->CopyTo(m_functor);

    return *this;
}

template <typename _Return, typename... _Args>
Delegate<_Return(_Args...)>& Delegate<_Return(_Args...)>::operator=(Delegate&& rhs) noexcept
{
    if (IsDynamicAllocated() && rhs.IsDynamicAllocated())
    {
        std::swap(m_functor, rhs.m_functor);
    }
    else if (rhs.IsDynamicAllocated())
    {
        std::swap(m_functor, rhs.m_functor);
        rhs.m_functor = nullptr;
    }
    else
    {
        if (IsDynamicAllocated())
        {
            std::swap(m_functor, rhs.m_functor);
        }

        m_storage = rhs.m_storage;
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    return *this;
}

template <typename _Return, typename... _Args>
constexpr bool Delegate<_Return(_Args...)>::operator==(std::nullptr_t rhs) const noexcept
{
    return m_functor == rhs;
}

template <typename _Return, typename... _Args>
constexpr bool Delegate<_Return(_Args...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return m_functor != rhs;
}

template <typename _Return, typename... _Args>
bool Delegate<_Return(_Args...)>::IsDynamicAllocated() const noexcept
{
    return m_functor != reinterpret_cast<const Functor*>(&m_storage[0]);
}

template <typename _Return, typename... _Args>
void Delegate<_Return(_Args...)>::Destroy()
{
    if (m_functor == nullptr)
    {
        return;
    }

    m_functor->Destroy();

    if (this->IsDynamicAllocated())
    {
        operator delete(m_functor);
    }

    m_storage = {};
}

}