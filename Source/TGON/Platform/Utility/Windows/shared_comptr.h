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
class TGON_API shared_comptr
{
	using ComptrType = _Ty;

public:
	// Set the pointer without increasing the reference count.
	void Attach( ComptrType* rawPtr )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->Relese( );
		}
	
		m_rawPtr = rawPtr;
	}

	// Set the pointer without decreasing the reference count.
	void Detach( )
	{
		m_rawPtr = nullptr;
	}

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
	shared_comptr( ) :
		m_rawPtr( nullptr )
	{
	}
	shared_comptr( ComptrType* rhs ) :
		m_rawPtr( rhs )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->AddRef( );
		}
	}
	shared_comptr( const shared_comptr& rhs ) :
		m_rawPtr( rhs.m_rawPtr )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->AddRef( );
		}
	}
	shared_comptr( shared_comptr&& rhs ) :
		m_rawPtr( rhs.m_rawPtr )
	{
		rhs.m_rawPtr = nullptr;
	}
	~shared_comptr( )
	{
		if ( m_rawPtr )
		{
			m_rawPtr->Release( );
			m_rawPtr = nullptr;
		}
	}

	shared_comptr& operator=( const shared_comptr& rhs )
	{
		if ( m_rawPtr == rhs.m_rawPtr )
		{
			return *this;
		}
	
		if ( m_rawPtr )
		{
			m_rawPtr->Release( );
		}
	
		rhs.m_rawPtr->AddRef( );
		m_rawPtr = rhs.m_rawPtr;
	
		return *this;
	}
	shared_comptr& operator=( shared_comptr&& rhs )
	{
		if ( m_rawPtr == rhs.m_rawPtr )
		{
			return *this;
		}

		if ( m_rawPtr )
		{
			m_rawPtr->Release( );
		}

		m_rawPtr = rhs.m_rawPtr;
		rhs.m_rawPtr = nullptr;

		return *this;
	}
	bool operator==( const shared_comptr& rhs )
	{
		return ( m_rawPtr == rhs.m_rawPtr );
	}
	bool operator!=( const shared_comptr& rhs )
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