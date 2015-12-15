#pragma once
#include <iostream>

class RTTI
{
public:
	static RTTI GetRTTI( ) {
		return ms_RTTI;
	}


private:
	static RTTI	ms_RTTI;
};
#define Implement_RTTI

#pragma once
#define RTTIInfo( classType )																		\
public:																									\
	virtual const CRTTI* GetRTTI( ) const { return &ms_RTTI; }								\
private:																								\
	friend CRTTI;																						\
	static const CRTTI ms_RTTI;																	\
	typedef classType RootType;

#define DeclareRootRTTI( classType )															\
	RTTIInfo( classType )																			\
	bool IsExactClass( const CRTTI* pRTTI ) const												\
	{																									\
		return GetRTTI( ) == pRTTI;																\
	}																									\
	bool IsKindOf( const CRTTI* pRTTI ) const													\
	{																									\
		const CRTTI* pBase = GetRTTI( );															\
		while ( pBase != NULL )																	\
		{																								\
			if ( pBase == pRTTI )																	\
			{																							\
				return true;																			\
			}																							\
			pBase = pBase->GetBaseRTTI( );														\
		}																								\
		return false;																					\
	}

#define DeclareRTTI( classType )																	\
	RTTIInfo( classType )																			\
	typedef __super::RootType RootType;

#define ImplementRootRTTI( classType ) const CRTTI classType::ms_RTTI( NULL )
#define ImplementRTTI( classType, BaseClassType ) const CRTTI classType::ms_RTTI( CRTTI::GetRTTI<BaseClassType>( ))

class CRTTI
{
public:
	template<typename T> static UINT GetTypeID( )
	{
		return reinterpret_cast<UINT>( &T::ms_RTTI );
	}
	template<typename T> static const CRTTI* GetRTTI( )
	{
		return &T::ms_RTTI;
	}

public:
	CRTTI( const CRTTI* pBaseRTTI )
		: m_pBaseRTTI( pBaseRTTI )
	{

	}

	~CRTTI( )
	{

	}

	const CRTTI* GetBaseRTTI( ) const
	{
		return m_pBaseRTTI;
	}

private:
	const CRTTI* m_pBaseRTTI;
};