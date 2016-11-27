/**
 * Author : Cha Junho
 * Date : 09/25/2016
 * Latest author :
 * Latest date :
 */

#pragma once
#include <type_traits>
#include <functional>
#include <boost/preprocessor/facilities/overload.hpp>

#include "../Template/TypeTraits.h"

/**
 * @note                Enable macro overloading
 * @ref                 http://www.boost.org/doc/libs/master/libs/preprocessor/doc/ref/overload.html
 */
#define TGON_MAKE_DELEGATE(...) BOOST_PP_CAT( BOOST_PP_OVERLOAD( TGON_MAKE_DELEGATE_, __VA_ARGS__ )( __VA_ARGS__ ), BOOST_PP_EMPTY( ))

/**
 * @note                Bind delegate with global function
 * @param   function    Type of function ( e.g. foo )
 */
#define TGON_MAKE_DELEGATE_1( function ) tgon::Delegate<tgon::function_traits<decltype( foo )>::function_type>::Bind<function>

/**
 * @note                Bind delegate with class member function
 * @param   function    Type of function ( e.g. &FooClass::foo )
 * @param   instance    Instance that receiving the event
 */
#define TGON_MAKE_DELEGATE_2( function, instance ) tgon::Delegate<tgon::function_traits<decltype( function )>::function_type>::Bind<tgon::function_traits<decltype( function )>::class_type, function>( instance )

namespace tgon
{

template <typename Ty>
class Delegate;

template <typename RetTy, typename... Args>
class Delegate<RetTy( Args... )> final
{
	using StubTy = RetTy(*)( void*, Args... );

/**
 * Ctor/Dtor
 */
public:
	Delegate( ) noexcept;
	Delegate( void* receiver, StubTy stub ) noexcept;
	~Delegate( ) noexcept = default;

/**
 * Operators
 */
	RetTy operator()( Args... args );

/**
 * Commands
 */
public:
    template <RetTy( *Handler )( Args... )>
    static Delegate Bind( ) noexcept;
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... )>
    static Delegate Bind( ReceiverTy* receiver ) noexcept;
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const>
    static Delegate Bind( ReceiverTy* receiver ) noexcept;
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) volatile>
    static Delegate Bind( ReceiverTy* receiver ) noexcept;
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const volatile>
    static Delegate Bind( ReceiverTy* receiver ) noexcept;

/**
 * Private methods
 */
private:
    template <RetTy( *Handler )( Args... )>
    static RetTy MakeStub( void* receiver, Args... args );
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... )>
    static RetTy MakeStub( void* receiver, Args... args );
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const>
    static RetTy MakeStub( void* receiver, Args... args );
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) volatile>
    static RetTy MakeStub( void* receiver, Args... args );
    
    template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const volatile>
    static RetTy MakeStub( void* receiver, Args... args );

/**
 * Private variables
 */
private:
	StubTy m_stub;
	void* m_receiver;
};

template<typename RetTy, typename ...Args>
inline Delegate<RetTy( Args... )>::Delegate( ) noexcept :
	m_receiver( nullptr ),
	m_stub( nullptr )
{
}

template<typename RetTy, typename ...Args>
inline Delegate<RetTy( Args... )>::Delegate( void* receiver, StubTy stub ) noexcept :
	m_receiver( receiver ),
	m_stub( stub )
{
}

template<typename RetTy, typename... Args>
inline RetTy Delegate<RetTy( Args... )>::operator()( Args... args )
{
	return m_stub( m_receiver, args... );
}


template<typename RetTy, typename ...Args>
template<RetTy( *Handler )( Args... )>
inline Delegate<RetTy( Args... )> Delegate<RetTy( Args... )>::Bind( ) noexcept
{
	return Delegate( nullptr, &MakeStub<Handler> );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... )>
inline Delegate<RetTy( Args... )> Delegate<RetTy( Args... )>::Bind( ReceiverTy* receiver ) noexcept
{
	return Delegate( receiver, &MakeStub<ReceiverTy, Handler> );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const>
inline Delegate<RetTy( Args... )> Delegate<RetTy( Args... )>::Bind( ReceiverTy* receiver ) noexcept
{
	return Delegate( receiver, &MakeStub<ReceiverTy, Handler> );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) volatile>
inline Delegate<RetTy( Args... )> Delegate<RetTy( Args... )>::Bind( ReceiverTy* receiver ) noexcept
{
	return Delegate( receiver, &MakeStub<ReceiverTy, Handler> );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... ) const volatile>
inline Delegate<RetTy( Args... )> Delegate<RetTy( Args... )>::Bind( ReceiverTy* receiver ) noexcept
{
	return Delegate( receiver, &MakeStub<ReceiverTy, Handler> );
}

template<typename RetTy, typename ...Args>
template<RetTy( *Handler )( Args... )>
inline RetTy Delegate<RetTy( Args... )>::MakeStub( void* receiver, Args... args )
{
	return Handler( args... );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, 
		 RetTy( ReceiverTy::* Handler )( Args... )>
inline RetTy Delegate<RetTy( Args... )>::MakeStub( void* receiver, Args... args )
{
	return ( reinterpret_cast<ReceiverTy*>( receiver )->*Handler )( args... );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, 
		 RetTy( ReceiverTy::* Handler )( Args... ) const>
inline RetTy Delegate<RetTy( Args... )>::MakeStub( void* receiver, Args... args )
{
	return ( reinterpret_cast<ReceiverTy*>( receiver )->*Handler )( args... );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, 
		 RetTy( ReceiverTy::* Handler )( Args... ) volatile>
inline RetTy Delegate<RetTy( Args... )>::MakeStub( void* receiver, Args... args )
{
	return ( reinterpret_cast<ReceiverTy*>( receiver )->*Handler )( args... );
}

template<typename RetTy, typename ...Args>
template<typename ReceiverTy, 
		 RetTy( ReceiverTy::* Handler )( Args... ) const volatile>
inline RetTy Delegate<RetTy( Args... )>::MakeStub( void* receiver, Args... args )
{
	return ( reinterpret_cast<ReceiverTy*>( receiver )->*Handler )( args... );
}

} /* namespace tgon */