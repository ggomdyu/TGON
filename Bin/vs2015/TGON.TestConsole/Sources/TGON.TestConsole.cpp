#include "PrecompiledHeader.h"
#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <Core/Math/Vector3.h>

#pragma once

#include <iostream>
#include <string>

class Hello
{
public:
    Hello() : msg("Hello") {}

    void execute(int n)
    {
        for(int i=0; i<n; ++i) {
            std::cout << msg;
        }
        std::cout << std::endl;
    }
private:
    std::string msg;
};

class World
{
public:
    World() : msg("World") {}

    void execute(int n)
    {
        for(int i=0; i<n; ++i) {
            std::cout << msg;
        }
        std::cout << std::endl;
    }
private:
    std::string msg;
};

class VirtualHello : virtual Hello
{
public:   
    void execute(int n) {
        std::cout << "VirtualHello" << std::endl;
    }
};

class HelloWorld : public Hello, public World
{
public:
    HelloWorld() {}

    void execute(int n)
    {
        Hello::execute(n);
        World::execute(n);
    }
};

class UnknownGreeting;
typedef void (UnknownGreeting::*UnknownExecute) (int n);



template<typename RetTy, typename... Args>
class TDelegate
{
	using DelegateChain = std::vector<std::function<RetTy( Args... )>>;


public:
	TDelegate( std::function<RetTy( Args... )> del ) :
		m_delegateChain{ del }
	{
	}

	TDelegate( )
	{

	}
	

public:
	void operator()( Args... args )
	{
		for ( auto& _delegate : m_delegateChain )
		{
			_delegate( args... );
		}
	}

	void operator=( const std::function<RetTy( Args... )>& del )
	{
		m_delegateChain.clear( );
		m_delegateChain.push_back( del );
	}

	void operator+=( const std::function<RetTy( Args... )>& del )
	{
		m_delegateChain.push_back( del );
	}


public:
	/*DelegateChain::iterator begin( )
	{
		return nullptr;
	}*/

	//DelegateChain::iterator end( )
	//{
	//	return m_delegateChain.end( );
	//}

	//DelegateChain::const_iterator cbegin( ) const
	//{
	//	return m_delegateChain.cbegin( );
	//}

	//DelegateChain::const_iterator cend( ) const
	//{
	//	return m_delegateChain.cend( );
	//}


private:
	DelegateChain m_delegateChain;
};

class SampleApplication
{
public:
	void Exec( )
	{

	}

	TDelegate<void, int> OnDestroy = [&]( int arg1 )
	{
		std::cout << "OnDestroy" << std::endl;
		n = arg1;
	};

	int n = 2342;
};

template <std::size_t N, std::size_t Exponent>
struct Pow
{
	enum { value = N * Pow<N, Exponent-1>::value };
};

template <std::size_t N>
struct Pow<N, 0>
{
	enum { value = 1 };
};


int main( int argc, char* argv[] )
{
	pow( 3, 4 );

	/*SampleApplication sa;
	sa.Exec( );

	sa.OnDestroy( 234 );*/

    return 0;
}


