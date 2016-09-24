#include "PrecompiledHeader.h"


#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

//
//template <typename T>
//class Delegate;
//
//template <typename RetTy, typename... Args>
//class Delegate<RetTy( Args... )>
//{
//public:
//	Delegate( ) : 
//		m_object( nullptr ), 
//		m_stub( nullptr )
//	{
//	}
//
//	template <class T, RetTy( T::*TMethod )( Args&&... ),
//			typename std::enable_if<>>
//	static Delegate from_method( T* object_ptr )
//	{
//		Delegate d;
//		d.m_object = object_ptr;
//		d.m_stub = &method_stub<T, TMethod>; // #1
//		
//		return d;
//	}
//
//	RetTy operator( )( Args&&... args ) const
//	{
//		return ( *m_stub )( m_object, std::forward<Args>( args )... );
//	}
//
//private:
//	using StubTy = RetTy(*)( void*, Args... );
//
//	template <class T, RetTy( T::*TMethod )( Args... )>
//	static RetTy method_stub( void* object_ptr, Args... args )
//	{
//		T* p = static_cast<T*>( object_ptr );
//		return ( p->*TMethod )( args... ); // #2
//	}
//
//private:
//	void* m_object;
//	StubTy m_stub;
//};
//
//class FooClass
//{
//public:
//	void foo( )
//	{
//		Delegate<void( )> del;
//		del.MakeStub<FooClass>( nullptr, nullptr );
//	}
//};

//template <typename Ty>
//struct Delegate;
//
//template <typename RetTy, typename... Args>

#include "Core/Template/TypeTraits.h"

template <typename Ty>
struct Delegate;

template <typename RetTy, typename... Args>
struct Delegate<RetTy( Args... )>
{
	using StubTy = RetTy(*)( void* );

	//
	// Con/Dtor
	//
public:
	Delegate( ) :
		m_receiver( nullptr ),
		m_stub( nullptr )
	{
	}

	Delegate( void* receiver, StubTy stub ) :
		m_receiver( receiver ),
		m_stub( stub )
	{
	}

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
	template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )()>
	static Delegate Bind( ReceiverTy* receiver )
	{
		Delegate d( receiver, &MakeStub<ReceiverTy, Handler> );
		return d;
	}

private:
	template <typename ReceiverTy, RetTy( ReceiverTy::*Handler )( )>
	static RetTy MakeStub( void* receiver )
	{
		ReceiverTy* castedReceiver = reinterpret_cast<ReceiverTy*>( receiver );
		return ( castedReceiver->*Handler )( );
	}

private:
	StubTy m_stub;
	void* m_receiver;
};

struct FooClass {
	int Foo( )
	{
		std::cout << "YAHO!" << std::endl;
		return 0;
	}
};


/* ex:  */
#define TGON_MAKE_DELEGATE( type, function, instance )\
	Delegate<type>::Bind<tgon::member_function_traits<decltype( function )>::class_type, function>( instance )

int main( int argc, char* argv[] )
{
	
	FooClass fc;
	auto d = TGON_MAKE_DELEGATE( int(), &FooClass::Foo, &fc );
	
	d( );

	return 0;
}

struct E_CREATE
{
	enum { value = 3 };
};
//
//template<typename RetTy, typename... Args>
//class Delegate
//{
//	using Type = RetTy(*)( void* callee, Args... );
//
//public:
//	Delegate( void* receiver, Type handlerFunc ) : 
//		m_receiver( receiver ),
//		m_handlerFunc( handlerFunc )
//	{
//	}
//
//	template <class T, RetTy( T::*TMethod )( Args... )>
//	static Delegate from_function( T* callee )
//	{
//		Delegate d( callee, &methodCaller<T, TMethod> );
//		return d;
//	}
//	RetTy operator()( Args... xs ) const
//	{
//		return ( *m_handlerFunc )( m_receiver, xs... );
//	}
//private:
//	void* m_receiver;
//	Type m_handlerFunc;
//	template <class T, RetTy( T::*TMethod )( Args... )>
//	static RetTy methodCaller( void* callee, Args... xs )
//	{
//		T* p = static_cast<T*>( callee );
//		return ( p->*TMethod )( xs... );
//	}
//};

////template <typename... Args>
//using stub_type = void(*)( void*, int );
//
//template <typename ReceiverTy, void( ReceiverTy::*Method )( ... )>
//void MethodStub( void* object )
//{
////	( static_cast<ReceiverTy*>( object )->*Method )( args... );
//}



