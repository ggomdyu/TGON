/*
* Author : Cha Junho
* Date : 05/17/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


template <typename RawPtrTy>
class shared_comptr
{
public:
	// Set the pointer without increasing the reference count.
	void Attach( RawPtrTy* rawPtr );

	// Set the pointer without decreasing the reference count.
	void Detach( );

	// Release and attach the pointer.
	void Reset( RawPtrTy* rawPtr );

	// Relese the pointer.
	void Release( );


public:
	shared_comptr( ) :
		m_rawPtr( nullptr )
	{
	}

	shared_comptr( RawPtrTy* rhs ) :
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
	
	RawPtrTy** operator&( )
	{
		return &m_rawPtr;
	}
	
	RawPtrTy* operator->( ) const
	{
		return m_rawPtr;
	}

	operator RawPtrTy*( ) const
	{
		return m_rawPtr;
	}

private:
	RawPtrTy* m_rawPtr;
};


template<typename RawPtrTy>
inline void shared_comptr<RawPtrTy>::Attach( RawPtrTy* rawPtr )
{
	if ( m_rawPtr )
	{
		m_rawPtr->Relese( );
	}

	m_rawPtr = rawPtr;
}

template<typename RawPtrTy>
inline void shared_comptr<RawPtrTy>::Detach( )
{
	m_rawPtr = nullptr;
}

template<typename RawPtrTy>
inline void shared_comptr<RawPtrTy>::Reset( RawPtrTy* rawPtr )
{
	this->Release( );
	if ( rawPtr )
	{
		rawPtr->AddRef( );
	}
}

template<typename RawPtrTy>
inline void shared_comptr<RawPtrTy>::Release( )
{
	if ( m_rawPtr )
	{
		m_rawPtr->Release( );
		m_rawPtr = nullptr;
	}
}


}