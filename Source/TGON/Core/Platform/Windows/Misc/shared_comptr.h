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
	 * Ctor/Dtor
	*/ 
public:
	shared_comptr( ) noexcept;
	shared_comptr( const shared_comptr& rhs );
	explicit shared_comptr( RawPtrTy* rhs );
	~shared_comptr( );

	/* @note	Swap the pointer. */
	shared_comptr( shared_comptr&& rhs );

	/* 
	 * Operators
	*/ 
	/* @note	Copy and Add reference count of pointer */
	shared_comptr& operator=( const shared_comptr& rhs );

	/*
	 * @note		Change the pointer owner of right handling side.
	 * @param	rhs	Original pointer owner
	*/
	shared_comptr& operator=( shared_comptr&& rhs );
	
	/*
	 * @note		Compare each owner's raw pointer
	 * @param	rhs	Raw pointer owner
	*/
	bool operator==( const shared_comptr& rhs );
	bool operator!=( const shared_comptr& rhs );
	
	/* @return	Raw pointer's reference */
	RawPtrTy** operator&( );
	
	/* @note	If accessed the pointer, then return the raw pointer that stored. */
	RawPtrTy* operator->( ) const;
	
	/* @note	Cast to raw pointer type */
	operator RawPtrTy*( ) const;

	/* 
	 * Commands
	*/ 
public:
	/*
	 * @note			Set the pointer without increasing the reference count.
	 * @param	rawPtr	Raw pointer which you want to attach
	*/
	void Attach( RawPtrTy* rawPtr );

	/* @note	Detach pointer without decreasing the reference count. */
	void Detach( );

	/*
	 * @note			Release and attach the pointer with increasing reference count.
	 * @rawPtr	raw		Pointer which you want to reset
	*/
	void Reset( RawPtrTy* rawPtr );

	/* @note	Relese the pointer */
	void Release( );

	/* 
	 * Variables
	*/ 
private:
	RawPtrTy* m_rawPtr;
};


template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::shared_comptr( ) noexcept :
	m_rawPtr( nullptr )
{
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::shared_comptr( RawPtrTy* rhs ) :
	m_rawPtr( rhs )
{
	if ( m_rawPtr )
	{
		m_rawPtr->AddRef( );
	}
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::~shared_comptr( )
{
	if ( m_rawPtr )
	{
		m_rawPtr->Release( );
		m_rawPtr = nullptr;
	}
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::shared_comptr( const shared_comptr& rhs ) :
	m_rawPtr( rhs.m_rawPtr )
{
	if ( m_rawPtr )
	{
		m_rawPtr->AddRef( );
	}
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::shared_comptr( shared_comptr&& rhs ) :
	m_rawPtr( rhs.m_rawPtr )
{
	rhs.m_rawPtr = nullptr;
}

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::operator=( const shared_comptr& rhs )
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

template<typename RawPtrTy>
inline shared_comptr<RawPtrTy>::operator=( shared_comptr&& rhs )
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
