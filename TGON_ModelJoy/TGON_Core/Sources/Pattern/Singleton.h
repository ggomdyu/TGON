/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-08
*/

#pragma once
#include <memory>


/*
	01. Constructor hideable singleton ( preprocessor ver. )
*/

#define DECLARE_STATIC_SINGLETON( type )					\
	static type* GetInstance( )										\
	{																		\
		static type instance;											\
		return &instance;												\
	}

#define DECLARE_DYNAMIC_SINGLETON( type )				\
	static const std::shared_ptr<type>& GetInstance( )		\
	{																		\
		static std::shared_ptr<type> instance;					\
																			\
		if ( !instance ) {													\
			instance.reset( new type );								\
		}																	\
		return instance;													\
	}


/*
	2. Constructor un-hideable singleton ( Inheritance ver. )

	Use DECLARE_STATIC_SINGLETON instead this
*/

template <typename type>
class StaticSingleton
{
public:
	static type* GetInstance( )
	{
		static type instance;
		return &instance;
	}

protected:
	StaticSingleton( )			{}
	~StaticSingleton( )			{}
};

template <typename type>
class DynamicSingleton
{
public:
	static const std::shared_ptr<type>& GetInstance( )
	{
		static std::shared_ptr<type> instance;

		if ( !instance ) {
			instance.reset( new type );
		}
		return instance;
	}

protected:
	DynamicSingleton( )		{}
	~DynamicSingleton( )		{}
};