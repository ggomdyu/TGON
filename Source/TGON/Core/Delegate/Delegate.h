//---------------------------------------------------------------------------------
// Author : Cha Junho
// Date : 09/25/2016
//---------------------------------------------------------------------------------

#pragma once
#include <type_traits>
#include "Core/Template/TypeTraits.h"

/* 
 * @note			Make and bind Delegate easily
 *						(ex): auto d = TGON_MAKE_DELEGATE( int(float), &FooClass::Foo, &fc );
 * @param type		Type of delegate ( e.g. int(), int(int), etc )
 * @param function	Original form of function ( e.g. &FooClass::foo )
 * @param instance	Interrupt receiver( Also it needs for member value capture )
*/
#define TGON_MAKE_DELEGATE( type, function, instance ) Delegate<type>::Bind<tgon::function_traits<decltype( function )>::class_type, function>( instance )


template <typename Ty>
class Delegate;

template <typename RetTy, typename... Args>
class Delegate<RetTy( Args... )> final
{
	using StubTy = RetTy(*)( void*, Args... );

	//
	// Con/Dtor
	//
public:
	Delegate( ) noexcept :
		m_receiver( nullptr ),
		m_stub( nullptr )
	{
	}
	Delegate( void* receiver, StubTy stub ) noexcept :
		m_receiver( receiver ),
		m_stub( stub )
	{
	}
	Delegate( const Delegate& ) noexcept = default;
	~Delegate( ) noexcept = default;

	//
	// Operators
	//
	RetTy operator()( Args&&... args )
	{
		return m_stub( m_receiver, std::forward<Args>( args )... );
	}

	//
	// Commands
	//
	template <typename ReceiverTy,
		RetTy( ReceiverTy::*Handler )( Args... ),
		typename = typename std::enable_if<std::is_class<ReceiverTy>::value>::type
	>
	static Delegate Bind( ReceiverTy* receiver ) noexcept
	{
		return Delegate( receiver, &MakeStub<ReceiverTy, Handler> );
	}

	//
	// Internal works
	//
private:
	template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( Args... )>
	static RetTy MakeStub( void* receiver, Args... args ) noexcept
	{
		return ( reinterpret_cast<ReceiverTy*>( receiver )->*Handler )( args... );
	}
	
	//
	// Private variables
	//
private:
	StubTy m_stub;
	void* m_receiver;
};