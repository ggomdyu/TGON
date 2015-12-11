/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-12-11
*/

/* Prev */
#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <memory>
	#include "Uncopyable.h"
#endif

#define SINGLETON_TYPE_STATIC

/*
	1. Constructor un-hideable singleton ( Inheritance ver. )
*/
template <typename T>
class Singleton
{
public:
	static const std::shared_ptr<T> GetInstance( )
	{
		if ( !m_Instance ) {
			m_Instance.reset( new T );
		}
		return m_Instance;
	}

protected:
	Singleton( ) {};
	~Singleton( ) {}

private:
	static std::shared_ptr<T> m_Instance;
};

template <typename T>
decltype( Singleton<T>::m_Instance ) Singleton<T>::m_Instance;

/*
	02. Constructor hideable singleton ( define ver. )
*/

#ifdef SINGLETON_TYPE_STATIC
#define Implement_Singleton_Instance( T )
#define Implement_Singleton( T )						\
public:															\
	static T* GetInstance( )									\
	{															\
		static T instance;										\
		return &instance;									\
	}
#elif defined SINGLETON_TYPE_DYNAMIC
#define Implement_Singleton( T )						\
public:															\
	static const std::shared_ptr<T> GetInstance( )		\
	{															\
		if ( !m_Instance ) {									\
			m_Instance.reset( new T );						\
		}														\
		return m_Instance;									\
	}															\
																\
private:														\
	static std::shared_ptr<T> m_Instance;	

#define Implement_Singleton_Instance( T )				\
namespace {													\
	decltype( T::m_Instance ) T::m_Instance;				\
}																		

#endif