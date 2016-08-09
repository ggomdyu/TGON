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
class unique_comptr final
{
public:
	/*
		Cons/Destructor
	*/
	unique_comptr( );

	~unique_comptr( );
	
	unique_comptr( RawPtrTy* rhs );

	unique_comptr( const unique_comptr& rhs ) = delete;

	unique_comptr( unique_comptr&& rhs );


	/*
		Operators
	*/
	unique_comptr& operator=( const unique_comptr& rhs ) = delete;
	
	unique_comptr& operator=( unique_comptr&& rhs );

	bool operator==( const unique_comptr& rhs );
	
	bool operator!=( const unique_comptr& rhs );
	
	RawPtrTy** operator&( );
	
	RawPtrTy* operator->( ) const;

	operator RawPtrTy*( ) const;


public:
	/*
		Commands
	*/
	// Release and attach the new pointer.
	void Reset( RawPtrTy* rawPtr );

	// Relese the pointer.
	void Release( );

	// Get the real pointer.
	RawPtrTy* Get( );


private:
	RawPtrTy* m_ptr;
};


template<typename RawPtrTy>
inline void unique_comptr<RawPtrTy>::Reset( RawPtrTy* rawPtr )
{
	this->Release( );
	if ( rawPtr )
	{
		rawPtr->AddRef( );
	}
}

template<typename RawPtrTy>
inline void unique_comptr<RawPtrTy>::Release( )
{
	if ( m_ptr )
	{
		m_ptr->Release( );
		m_ptr = nullptr;
	}
}

template<typename RawPtrTy>
inline RawPtrTy* unique_comptr<RawPtrTy>::Get( )
{
	return m_ptr;
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>::unique_comptr( ) :
	m_ptr( nullptr )
{
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>::unique_comptr( RawPtrTy* rhs ) :
	m_ptr( rhs )
{
	if ( m_ptr )
	{
		m_ptr->AddRef( );
	}
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>::unique_comptr( unique_comptr&& rhs ) :
	m_ptr( rhs.m_ptr )
{
	rhs.m_ptr = nullptr;
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>::~unique_comptr( )
{
	if ( m_ptr )
	{
		m_ptr->Release( );
		m_ptr = nullptr;
	}
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>& unique_comptr<RawPtrTy>::operator=( unique_comptr&& rhs )
{
	m_ptr = rhs.m_ptr;
	rhs.m_ptr = nullptr;
}

template<typename RawPtrTy>
inline bool unique_comptr<RawPtrTy>::operator==( const unique_comptr& rhs )
{
	return ( m_ptr == rhs.m_ptr );
}

template<typename RawPtrTy>
inline bool unique_comptr<RawPtrTy>::operator!=( const unique_comptr& rhs )
{
	return ( m_ptr != rhs.m_ptr );
}

template<typename RawPtrTy>
inline RawPtrTy** unique_comptr<RawPtrTy>::operator&( )
{
	return &m_ptr;
}

template<typename RawPtrTy>
inline RawPtrTy* unique_comptr<RawPtrTy>::operator->( ) const
{
	return m_ptr;
}

template<typename RawPtrTy>
inline unique_comptr<RawPtrTy>::operator RawPtrTy*( ) const
{
	return m_ptr;
}


}
