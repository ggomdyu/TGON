/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-08
* Description : Deprecated
*/

#pragma once
//#include <memory>


/*
	Normal
*/
//#define DECLARE_STATIC_SINGLETON( type )					\
//	static type* GetInstance( )								\
//	{														\
//		static type instance;								\
//		return &instance;									\
//	}

/*
	Special
*/
// trash code
//#define DECLARE_DYNAMIC_SINGLETON( )						\
//private:													\
//	template<typename base_t>								\
//	inline static base_t owner_tag( void( base_t::* )( ));	\
//															\
//	void internal_tag( );									\
//	typedef decltype( owner_tag( &internal_tag )) this_t;	\
//															\
//public:													\
//	friend std::default_delete<this_t>;						\
//	static const std::unique_ptr<this_t>& GetInstance( )	\
//	{														\
//		static std::unique_ptr<this_t> instance;			\
//		if ( !instance )									\
//		{													\
//			instance.reset( new this_t );					\
//		}													\
//		return instance;									\
//	}