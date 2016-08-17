// TGON.TestConsole.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "PrecompiledHeader.h"
//#include <boost/signals2.hpp>
#include <iostream>
#include <vector>
#include <cstdint>


class TEvent;
class TObserver
{
public:
	TObserver( )
	{
	}

	virtual ~TObserver( ) = 0
	{
	};

public:

public:
	virtual void Update( ) = 0;
};

class TEvent
{
public:
	void Attach( TObserver* observer )
	{
		m_observerList.push_back( observer );
	}

	virtual void Notify( )
	{
		for ( TObserver* observer : m_observerList )
		{
			observer->Update( );
		}
	}

	virtual uint32_t GetHashCode( ) const = 0;


private:
	std::vector<TObserver*> m_observerList;
};

class TErrorEvent :
	public TEvent
{
public:
	int GetErrorCode( ) const
	{ 
		return m_errCode; 
	}

	virtual uint32_t GetHashCode( ) const
	{
		return 194;
	}

private:
	int m_errCode;
};

class TErrorEventHandler : public TObserver
{
public:
	TErrorEventHandler( TErrorEvent* errEvent ) :
		m_errEvent( errEvent )
	{
		errEvent->Attach( this );
		//m_errEvent->Detach( this );
	}

	virtual void Update( )
	{
		MessageBox( 0,0,0,0 );
	}

private:
	TErrorEvent* m_errEvent;
};

class TEventReceiver
{
public:

private:
	static std::map<uint32_t, TEvent> m_eventList;
};

class FOO_CLASS :
	public TEventReceiver
{
public:
	FOO_CLASS( )
	{

	}

	virtual ~FOO_CLASS( )
	{

	}

public:
};

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


