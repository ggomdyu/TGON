// TGON.TestConsole.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "PrecompiledHeader.h"

#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <boost/lexical_cast.hpp>
#include <Object/TObject.h>
#include <Core/Object/TEventSubject.h>


namespace tgon
{
	//class TEventSubject;
}


struct OnDestroy {};
struct OnMouseDown {};



//template <typename... Args>
//struct STR
//{
//};



class WOWOW :
	public tgon::TEventSubject
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( WOWOW, tgon::TEventSubject )

public:
	WOWOW( )
	{
		this->SubscribeEvent<E_DESTROY>( &WOWOW::OnDestroy );
	}

private:
	void OnDestroy( int a, int b )
	{
		std::cout << a + b << std::endl;
		m = 3251;
	}

public:
	void Update( )
	{
		this->NotifyEvent<E_DESTROY>( 3241,1 );
	}

	int m = -234;
};

//class TEST
//{
//public:
//	template <class T, class T2>
//	void foo( T, T2 );
//};
//
//template<class T, class T2>
//void TEST::foo( T, T2 )
//{
//	std::cout << "0" << std::endl;
//}
//
//template<class T2>
//void TEST::foo<float>( float arg )
//{
//	std::cout << "1" << std::endl;
//}


// ConsoleApplication6.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <iostream>

#include <iostream>
#include <complex>

//
// Event types
//
class E_DESTROY;
class E_MOVED;

//
// Event handler template
//
class EventSubject;
class EventHandler
{
public:
	explicit EventHandler( EventSubject* receiver ) :
		m_receiver( receiver )
	{
	}

	virtual ~EventHandler( )
	{
	}
	
	EventSubject* GetReceiver( )
	{ 
		return m_receiver;
	}
	
private:
	EventSubject* m_receiver;
};

template <typename EventTy>
class EventHandlerImpl :
	public EventHandler
{
public:
	explicit EventHandlerImpl( EventSubject* receiver ) :
		EventHandler( receiver )
	{
	}

	//virtual void NotifyEvent( /*Variadic arguments*/ ) = 0;
};
//
//template<>
//class EventHandlerImpl<E_DESTROY>
//{
//public:
//	void NotifyEvent( int arg1, int arg2 )
//	{
//		std::cout << arg1 + arg2 << std::endl;
//	}
//};
//
//template<>
//class EventHandlerImpl<E_MOVED>
//{
//public:
//	void NotifyEvent( int arg1 )
//	{
//		std::cout << arg1 << std::endl;
//	}
//};

class EventSubject
{
public:
	template <typename EventTy>
	void SubscribeEvent( )
	{
		static_assert( false, "You can't use unspecialized template of NotifyEvent. You can specialize easily by TGON_GENERATE_EVENT macro." );
		//auto handler = EventHandlerImpl<E_DESTROY>( this );
		//m_eventHandler = handler;
	}

	template <typename EventTy, typename... HandlerFuncArgs>
	void NotifyEvent( HandlerFuncArgs... args ) // = delete;
	{
		static_assert( false, "You can't use unspecialized template of NotifyEvent. You can specialize easily by TGON_GENERATE_EVENT macro." );
	}

private:
	EventHandler* m_eventHandler;
};

template<>
void EventSubject::NotifyEvent<E_DESTROY>( int n )
{
	std::cout << n << std::endl;
}


int main( int argc, char* argv[] )
{

	//std::couta.foo<2, 3>( );

	///*TWorkThread tt;
	//DWORD b = GetTickCount( );

	//std::atomic<int> v = 0;
	//auto work = [&]( )
	//{
	//	int temp = 0;
	//	for ( int i = 0 ; i < 25000000; ++i )
	//		temp += 1;

	//	v += temp;
	//};

	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//tt.Request( work );
	//
	//std::cout << "b";
	//tt.Wait( );
	//std::cout << "a";

	//DWORD e = GetTickCount( ) - b;

	//std::cout << v;

	//Sleep( 10000 );

	//std::cout << v.load( ) << ", 걸린 시간: " << e;


	//return  0;*/
	//{

	//TWorkThreadModule tw;

	//DWORD b = GetTickCount( );

	//std::atomic<int> v = 0;
	//auto work = [&]( )
	//{
	//	int temp = 0;
	//	for ( int i = 0; i < 25000000; ++i )
	//		temp += 1;

	//	v += temp;
	//};

	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );
	//tw.Request( work );

	//std::cout << "a";
	//tw.Wait( );
	//std::cout << "b";



	//DWORD e = GetTickCount( ) - b;

	//
	//std::cout << v << " "<<e << std::endl;
	//}



    return 0;
}


