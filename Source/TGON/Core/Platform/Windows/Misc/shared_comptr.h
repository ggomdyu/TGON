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
	/*
		Ctor/Dtor
	*/
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


	/*
		Operators
	*/
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
	
	bool operator==( const shared_comptr& rhs );
	
	bool operator!=( const shared_comptr& rhs );
	
	RawPtrTy** operator&( );

	RawPtrTy* operator->( ) const;

	operator RawPtrTy*( ) const;


	/*
		Commands
	*/
public:
	//
	// Set the pointer without increasing the reference count.
	//
	// @param rawPtr raw pointer you want to attach
	//
	void Attach( RawPtrTy* rawPtr );

	//
	// Detach pointer without decreasing the reference count.
	//
	void Detach( );

	//
	// Release and attach the pointer with increasing reference count.
	//
	// @rawPtr raw pointer you want to reset
	//
	void Reset( RawPtrTy* rawPtr );

	//
	// Relese the pointer.
	//
	void Release( );


	/*
		Private variables
	*/
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

template<typename RawPtrTy>
inline bool shared_comptr<RawPtrTy>::operator==( const shared_comptr& rhs )
{
	return ( m_rawPtr == rhs.m_rawPtr );
}

template<typename RawPtrTy>
inline bool shared_comptr<RawPtrTy>::operator!=( const shared_comptr& rhs )
{
	return ( m_rawPtr != rhs.m_rawPtr );
}

template<typename RawPtrTy>
inline RawPtrTy** shared_comptr<RawPtrTy>::operator&( )
{
	return &m_rawPtr;
}

template<typename RawPtrTy>
inline RawPtrTy* shared_comptr<RawPtrTy>::operator->( ) const
{
	return m_rawPtr;
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::operator RawPtrTy*( ) const
{
	return m_rawPtr;
}


}
