/*		
* Author : Cha Junho
* Date : 05/17/2016
* Latest author :
* Latest date :
*/


#pragma once


namespace tgon
{


template <typename PtrTy>
class unique_comptr final
{
public:
	/*
		Cons/Destructor
	*/
	unique_comptr( );

	~unique_comptr( );
	
	unique_comptr( PtrTy* rhs );

	unique_comptr( const unique_comptr& rhs ) = delete;

	unique_comptr( unique_comptr&& rhs );


	/*
		Operators
	*/
	unique_comptr& operator=( const unique_comptr& rhs ) = delete;
	
	unique_comptr& operator=( unique_comptr&& rhs );

	bool operator==( const unique_comptr& rhs );
	
	bool operator!=( const unique_comptr& rhs );
	
	PtrTy** operator&( );
	
	PtrTy* operator->( ) const;

	operator PtrTy*( ) const;


public:
	/*
		Commands
	*/
	// Release and attach the new pointer.
	void Reset( PtrTy* rawPtr );

	// Relese the pointer.
	void Release( );

	// Get the real pointer.
	PtrTy* Get( );


private:
	PtrTy* m_ptr;
};


template<typename PtrTy>
inline void unique_comptr<PtrTy>::Reset( PtrTy* rawPtr )
{
	this->Release( );
	if ( rawPtr )
	{
		rawPtr->AddRef( );
	}
}

template<typename PtrTy>
inline void unique_comptr<PtrTy>::Release( )
{
	if ( m_ptr )
	{
		m_ptr->Release( );
		m_ptr = nullptr;
	}
}

template<typename PtrTy>
inline PtrTy* unique_comptr<PtrTy>::Get( )
{
	return m_ptr;
}

template<typename PtrTy>
inline unique_comptr<PtrTy>::unique_comptr( ) :
	m_ptr( nullptr )
{
}

template<typename PtrTy>
inline unique_comptr<PtrTy>::unique_comptr( PtrTy* rhs ) :
	m_ptr( rhs )
{
	if ( m_ptr )
	{
		m_ptr->AddRef( );
	}
}

template<typename PtrTy>
inline unique_comptr<PtrTy>::unique_comptr( unique_comptr&& rhs ) :
	m_ptr( rhs.m_ptr )
{
	rhs.m_ptr = nullptr;
}

template<typename PtrTy>
inline unique_comptr<PtrTy>::~unique_comptr( )
{
	if ( m_ptr )
	{
		m_ptr->Release( );
		m_ptr = nullptr;
	}
}

template<typename PtrTy>
inline unique_comptr<PtrTy>& unique_comptr<PtrTy>::operator=( unique_comptr&& rhs )
{
	m_ptr = rhs.m_ptr;
	rhs.m_ptr = nullptr;
}

template<typename PtrTy>
inline bool unique_comptr<PtrTy>::operator==( const unique_comptr& rhs )
{
	return ( m_ptr == rhs.m_ptr );
}

template<typename PtrTy>
inline bool unique_comptr<PtrTy>::operator!=( const unique_comptr& rhs )
{
	return ( m_ptr != rhs.m_ptr );
}

template<typename PtrTy>
inline PtrTy** unique_comptr<PtrTy>::operator&( )
{
	return &m_ptr;
}

template<typename PtrTy>
inline PtrTy* unique_comptr<PtrTy>::operator->( ) const
{
	return m_ptr;
}

template<typename PtrTy>
inline unique_comptr<PtrTy>::operator PtrTy*( ) const
{
	return m_ptr;
}


}