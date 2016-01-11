/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-08
*/

#pragma once
#include <memory>

/*
	1. Constructor un-hideable singleton ( Inheritance ver. )

	User can inherit through support friend this
	but It makes desultory interface, so I hope u all using Declare_Static_Singleton instead
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
	StaticSingleton( )			{}
	~StaticSingleton( )			{}
};

template <typename T>
class DynamicSingleton
{
public:
	static const std::shared_ptr<T>& GetInstance( )
	{
		static std::shared_ptr<T> instance;

		if ( !instance ) {
			instance.reset( new T );
		}
		return instance;
	}

protected:
	DynamicSingleton( )		{}
	~DynamicSingleton( )		{}
};

/*
	02. Constructor hideable singleton ( preprocessor ver. )
*/

#define Declare_Static_Singleton( T )							\
	static T* GetInstance( )										\
	{																	\
		static T instance;											\
		return &instance;											\
	}

#define Declare_Dynamic_Singleton( T )						\
	static const std::shared_ptr<T>& GetInstance( )		\
	{																	\
		static std::shared_ptr<T> instance;					\
																		\
		if ( !instance ) {												\
			instance.reset( new T );								\
		}																\
		return instance;												\
	}					