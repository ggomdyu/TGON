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

template <typename _ReturnType, typename... _ArgTypes>
class Functor
{
/**@section Destructor */
public:
    virtual ~Functor() = default;

/**@section Method */
public:
    virtual _ReturnType Invoke(_ArgTypes... args) const = 0;
    virtual void CopyTo(Functor* functor) const = 0;
    virtual void Destroy() = 0;
    virtual size_t GetBytes() const noexcept = 0;
};

template <typename _FunctionType, bool IsMemberFunction>
struct FunctorImplParam;

template <typename _FunctionType>
struct FunctorImplParam<_FunctionType, false>
{
    _FunctionType function;
};

template <typename _FunctionType>
struct FunctorImplParam<_FunctionType, true>
{
    _FunctionType function;
    void* receiver;
};

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
class FunctorImpl final :
    public Functor<_ReturnType, _ArgTypes...>
{
/**@section Type */
public:
    using FunctorImplParam = FunctorImplParam<_FunctionType, FunctionTraits<_FunctionType>::IsMemberFunction>;
    
/**@section Constructor */
public:
    explicit FunctorImpl(const FunctorImplParam& param) noexcept;
    explicit FunctorImpl(FunctorImplParam&& param) noexcept;
    
/**@section Method */
public:
    _ReturnType Invoke(_ArgTypes... args) const override;
    void CopyTo(Functor<_ReturnType, _ArgTypes...>* functor) const override;
    void Destroy() override;
    size_t GetBytes() const noexcept override;

/**@section Variable */
private:
    FunctorImplParam m_param;
};

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::FunctorImpl(const FunctorImplParam& param) noexcept :
    m_param(param)
{
}

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::FunctorImpl(FunctorImplParam&& param) noexcept :
    m_param(std::move(param))
{
}

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline void FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::CopyTo(Functor<_ReturnType, _ArgTypes...>* functor) const
{
    new (functor) FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>(m_param);
}

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline _ReturnType FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::Invoke(_ArgTypes... args) const
{
    if constexpr (FunctionTraits<_FunctionType>::IsMemberFunction)
    {
        return (reinterpret_cast<typename FunctionTraits<_FunctionType>::ClassType*>(m_param.receiver)->*(m_param.function))(args...);
    }
    else
    {
        return m_param.function(args...);
    }
}

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline void FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::Destroy()
{
    if constexpr (FunctionTraits<_FunctionType>::IsFunctor)
    {
        m_param.function.~_FunctionType();
    }
}

template <typename _FunctionType, typename _ReturnType, typename... _ArgTypes>
inline size_t FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>::GetBytes() const noexcept
{
    return sizeof(*this);
}

}

template <typename _Type>
constexpr bool IsDelegate = detail::IsDelegate<_Type>::value;

template <typename _ReturnType, typename... _ArgTypes>
class Delegate<_ReturnType(_ArgTypes...)> final
{
/**@section Type */
public:
    using ReturnType = _ReturnType;

private:
    template <typename _FunctionType>
    using FunctorImpl = detail::FunctorImpl<_FunctionType, _ReturnType, _ArgTypes...>;
    using Functor = detail::Functor<_ReturnType, _ArgTypes...>;

/**@section Constructor */
public:
    constexpr Delegate() noexcept = default;
    constexpr Delegate(std::nullptr_t) noexcept;
    Delegate(const Delegate& rhs);
    Delegate(Delegate&& rhs) noexcept;
    template <typename _FunctionType, typename std::enable_if_t<!IsDelegate<RemoveCvref<_FunctionType>>>* = nullptr>
    Delegate(_FunctionType&& function);
    template <typename _FunctionType, typename std::enable_if_t<!IsDelegate<RemoveCvref<_FunctionType>>>* = nullptr>
    Delegate(_FunctionType&& function, void* receiver);

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
    template <typename _FunctionType>
    static constexpr bool IsLargeFunction() noexcept;
    bool IsDynamicAllocated() const noexcept;
    void Destroy();

/**@section Variable */
private:
    static constexpr size_t StorageCapacity = 7;

    Functor* m_functor;
    std::array<void*, StorageCapacity> m_storage = {};
};

template <typename _FunctionType>
Delegate(_FunctionType&& function) -> Delegate<typename FunctionTraits<RemoveCvref<_FunctionType>>::FunctionType>;

template <typename _FunctionType>
Delegate(_FunctionType&& function, void* receiver) -> Delegate<typename FunctionTraits<RemoveCvref<_FunctionType>>::FunctionType>;

template <typename _ReturnType, typename... _ArgTypes>
constexpr Delegate<_ReturnType(_ArgTypes...)>::Delegate(std::nullptr_t) noexcept :
    Delegate()
{
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(const Delegate& rhs) :
    Delegate()
{
    if (rhs.m_functor == nullptr)
    {
        return;
    }

    m_functor = reinterpret_cast<Functor*>(rhs.IsDynamicAllocated() ? operator new(rhs.m_functor->GetBytes()) : &m_storage[0]);

    rhs.m_functor->CopyTo(m_functor);
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(Delegate&& rhs) noexcept :
    Delegate()
{
    if (rhs.m_functor == nullptr)
    {
        return;
    }

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

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType, typename std::enable_if_t<!IsDelegate<RemoveCvref<_FunctionType>>>*>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType&& function) :
    Delegate()
{
    using FunctionType = std::decay_t<_FunctionType>;
    if constexpr (Delegate::IsLargeFunction<FunctionType>())
    {
        m_functor = reinterpret_cast<Functor*>(operator new(sizeof(FunctorImpl<FunctionType>)));
    }
    else
    {
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }
    
    new (m_functor) FunctorImpl<FunctionType>({std::forward<_FunctionType>(function)});
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType, typename std::enable_if_t<!IsDelegate<RemoveCvref<_FunctionType>>>*>
inline Delegate<_ReturnType(_ArgTypes...)>::Delegate(_FunctionType&& function, void* receiver) :
    Delegate()
{
    using FunctionType = std::decay_t<_FunctionType>;
    if constexpr (Delegate::IsLargeFunction<FunctionType>())
    {
        m_functor = reinterpret_cast<Functor*>(operator new(sizeof(FunctorImpl<FunctionType>)));
    }
    else
    {
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    new (m_functor) FunctorImpl<FunctionType>({std::forward<_FunctionType>(function), receiver});
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>::~Delegate()
{
    this->Destroy();
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename... _ArgTypes2>
inline _ReturnType Delegate<_ReturnType(_ArgTypes...)>::operator()(_ArgTypes2&&... args) const
{
    if (m_functor == nullptr)
    {
        return _ReturnType();
    }

    return m_functor->Invoke(std::forward<_ArgTypes2>(args)...);
}

template <typename _ReturnType, typename... _ArgTypes>
template <typename _FunctionType>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::IsLargeFunction() noexcept
{
    return sizeof(FunctorImpl<_FunctionType>) > (sizeof(m_storage) - sizeof(m_storage[0]));
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(const Delegate& rhs)
{
    this->Destroy();

    if (rhs.m_functor == nullptr)
    {
        return *this;
    }

    m_functor = reinterpret_cast<Functor*>(rhs.IsDynamicAllocated() ? operator new(rhs.m_functor->GetBytes()) : &m_storage[0]);

    rhs.m_functor->CopyTo(m_functor);

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
inline Delegate<_ReturnType(_ArgTypes...)>& Delegate<_ReturnType(_ArgTypes...)>::operator=(Delegate&& rhs) noexcept
{
    if (rhs.IsDynamicAllocated())
    {
        std::swap(m_functor, rhs.m_functor);
    }
    else
    {
        m_storage = rhs.m_storage;
        m_functor = reinterpret_cast<Functor*>(&m_storage[0]);
    }

    return *this;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(std::nullptr_t rhs) const noexcept
{
    return m_functor == rhs;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(std::nullptr_t rhs) const noexcept
{
    return m_functor != rhs;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator==(const Delegate& rhs) const noexcept
{
    return m_functor == rhs.m_functor;
}

template <typename _ReturnType, typename... _ArgTypes>
constexpr bool Delegate<_ReturnType(_ArgTypes...)>::operator!=(const Delegate& rhs) const noexcept
{
    return m_functor != rhs.m_functor;
}

template <typename _ReturnType, typename... _ArgTypes>
inline bool Delegate<_ReturnType(_ArgTypes...)>::IsDynamicAllocated() const noexcept
{
    return m_functor != reinterpret_cast<const Functor*>(&m_storage[0]);
}

template <typename _ReturnType, typename... _ArgTypes>
inline void Delegate<_ReturnType(_ArgTypes...)>::Destroy()
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