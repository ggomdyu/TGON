/*
* Author : Cha Junho
* Date : 05/22/2016
* Latest author : 
* Latest date : 
*/


#pragma once

namespace tgon
{


class AbstractSingleton
{
public:
	virtual void Setup( ) {};
	virtual void Release( ) {};
};

template <class _InstTy>
class TSingleton : public AbstractSingleton
{
private:
	class SingletonInhProxy : public _InstTy {};

public:
	static _InstTy* Get( )
	{
		static SingletonInhProxy spInst;
		return &spInst;
	}

protected:
	TSingleton( ) {}
	virtual ~TSingleton( ) {}
};


}

//template <class _Ty>
//class TSingletonDynamic : public ISingleton
//{
//private:
//	class SingletonInhProxy : public _Ty 
//	{
//		friend std::default_delete<_Ty>;
//	};
//
//public:
//	static _Ty* Get( )
//	{
//		// TODO : Induce this code to inline
//		static std::unique_ptr<SingletonInhProxy> 
//			spInstPtr( new SingletonInhProxy );
//		return spInstPtr.get();
//	}
//
//	virtual void Release( ) override {}
//
//protected:
//	TSingletonDynamic( ) {}
//	virtual ~TSingletonDynamic( ) {}
//};


// Deprecated...
/*
#define DECLARE_DYNAMIC_SINGLETON( )\
private:\
	template<typename base_t>\
	inline static base_t owner_tag( void( base_t::* )( ));\
\
	void internal_tag( );\
	typedef decltype( owner_tag( &internal_tag )) this_t;\
\
public:\
	static const std::unique_ptr<this_t>& Get( )\
	{\
	}
*/