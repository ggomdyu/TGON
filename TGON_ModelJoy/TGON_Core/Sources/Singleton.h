/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-12-15
*/

#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <memory>
#endif

/*
	1. Constructor un-hideable singleton ( Inheritance ver. )
*/

template <typename T>
class StaticSingleton
{
public:
	static const T* GetInstance( )
	{
		static T instance;
		return &instance;
	}

protected:
	StaticSingleton( )		{}
	~StaticSingleton( )		{}
};

template <typename T>
class DynamicSingleton
{
public:
	static const std::shared_ptr<T>& GetInstance( )
	{
		if ( !m_instance ) {
			m_instance.reset( new T );
		}
		return m_instance;
	}

protected:
	DynamicSingleton( )		{}
	~DynamicSingleton( )		{}

private:
	static std::shared_ptr<T> m_instance;
};

/*
	02. Constructor hideable singleton ( define ver. )
*/

#define Declare_Static_Singleton( T )						\
	static T* GetInstance( )										\
	{																	\
		static T instance;											\
		return &instance;											\
	}

#define Declare_Dynamic_Singleton( T )					\
public:																\
	static const std::shared_ptr<T>& GetInstance( )		\
	{																	\
		if ( !m_instance ) {											\
			m_instance.reset( new T );							\
		}																\
		return m_instance;											\
	}																	\
																		\
private:																\
	static std::shared_ptr<T> m_instance;	

#define Implement_Singleton_Instance( T )					\
namespace {														\
	decltype( typename T::m_instance ) T::m_instance;	\
}											