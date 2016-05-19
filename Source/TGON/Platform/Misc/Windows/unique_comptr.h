/*		
* Author : Junho-Cha
* Date : 05/17/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Config/Build.h"


namespace tgon
{


template <typename _Ty>
class TGON_API unique_comptr
{
	using ComptrType = _Ty;

public:
	// Release and attach the pointer.
	void Reset( ComptrType* rawPtr )
	{
		this->Release( );
		if ( rawPtr )
		{
			rawPtr->AddRef( );
		}
	}

	// Relese the pointer.
	void Release( )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->Release( );
			m_rawPtr = nullptr;
		}
	}

public:
	unique_comptr( ) :
		m_rawPtr( nullptr )
	{
	}
	unique_comptr( ComptrType* rhs ) :
		m_rawPtr( rhs )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->AddRef( );
		}
	}
	unique_comptr( const unique_comptr& rhs ) = delete;
	~unique_comptr( )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->Release( );
			m_rawPtr = nullptr;
		}
	}

	unique_comptr& operator=( const unique_comptr& rhs ) = delete;
	bool operator==( const unique_comptr& rhs )
	{
		return ( m_rawPtr == rhs.m_rawPtr );
	}
	bool operator!=( const unique_comptr& rhs )
	{
		return ( m_rawPtr != rhs.m_rawPtr );
	}
	ComptrType** operator&( )
	{
		return &m_rawPtr;
	}
	ComptrType* operator->( ) const
	{
		return m_rawPtr;
	}

	operator ComptrType*( ) const
	{
		return m_rawPtr;
	}

private:
	ComptrType* m_rawPtr;
};


}