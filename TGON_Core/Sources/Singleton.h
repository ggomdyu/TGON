/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/

/* Prev */
#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <memory>
	#include "Uncopyable.h"
#endif

/*
	Unsafe to multi-thread
*/
template <typename T>
class CSingleton : private Uncopyable
{
public:
	static const std::shared_ptr<T> get( )
	{
		if ( !m_Instance ) {
			m_Instance.reset( new T );
		}
		return m_Instance;
	}

protected:
	CSingleton( ) {}
	~CSingleton( ) {}

private:
	static std::shared_ptr<T> m_Instance;
};

template <typename T>
decltype( CSingleton<T>::m_Instance ) CSingleton<T>::m_Instance;

/*
	TODO: If using multi-thread, use the follow singleton code
*/
//template <typename T>
//class CSingleton
//{
//public:
//	static T& get( )
//	{
//		static T instance;
//		return instance;
//	}
//
//protected:
//	CSingleton( ) {};
//	~CSingleton( ) {};
//};