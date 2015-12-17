/*
* 작성자 : 차준호
* 작성일 : 2015-12-14
* 최종 수정 : 차준호
* 최종 수정일 : 2015-12-16
*/

#pragma once

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <iostream>
#endif



class RTTI
{
public:
	RTTI( const RTTI* parent );
	~RTTI( );

	const RTTI*											GetParentRTTI( ) const		{ return m_parentRTTI; }
	template <class T> static const RTTI*		GetRTTI( )						{ return &T::ms_RTTI; }
	template <class T> static uint32_t				GetTypeHash( )					{ return reinterpret_cast<uint32_t>( &T::ms_RTTI ); }

private:
	const RTTI*	m_parentRTTI;
};



#define Declare_RTTI( )															\
private:																				\
	friend RTTI;																		\
	static const RTTI		ms_RTTI;												\
																						\
public:																				\
	 virtual const RTTI*	GetRTTI( ) const		{ return &ms_RTTI; }


#define Implement_Root_RTTI( ownerType )								\
	decltype( ownerType::ms_RTTI ) ownerType::ms_RTTI( nullptr );

#define Implement_RTTI( ownerType, parentType )						\
	decltype( ownerType::ms_RTTI ) ownerType::ms_RTTI( RTTI::GetRTTI<parentType>( ));