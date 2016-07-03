/*		
* Author : Cha Junho
* Date : 05/17/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


template <typename _RawPtrTy>
class unique_comptr
{
public:
	// Release and attach the pointer.
	void Reset( _RawPtrTy* rawPtr )
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
	unique_comptr( _RawPtrTy* rhs ) :
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
	_RawPtrTy** operator&( )
	{
		return &m_rawPtr;
	}
	_RawPtrTy* operator->( ) const
	{
		return m_rawPtr;
	}

	operator _RawPtrTy*( ) const
	{
		return m_rawPtr;
	}

private:
	_RawPtrTy* m_rawPtr;
};


}