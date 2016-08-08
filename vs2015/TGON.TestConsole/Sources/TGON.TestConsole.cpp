// TGON.TestConsole.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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


template<typename... Args>
using VariadicFuncPtr = void(*)( Args... );


struct E_DESTROY : 
	public tgon::TObject
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( E_DESTROY, TObject )
};

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

	void OnDestroy( int a, int b, int c )
	{
		std::cout << a + b + c << std::endl;
	}

	void Update( )
	{
		this->NotifyEvent<E_DESTROY, WOWOW>( 1,1,1 );
	}

	int m = -234;
};

template <typename ReceiverTy, typename... HandlerFuncArgs>
using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

int main()
{
	WOWOW a;
	a.Update( );
	WOWOW b;
	b.Update( );
	WOWOW c;
	c.Update( );

	//VariadicFuncPtr<int> a;
	int  v = 3;

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

	//std::cout << v.load( ) << ", �ɸ� �ð�: " << e;


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

