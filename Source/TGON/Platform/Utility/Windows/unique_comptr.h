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
class unique_comptr final
{
public:
	/*
		Cons/Destructor
	*/
	unique_comptr( );

	explicit unique_comptr( _RawPtrTy* rhs );
	
	~unique_comptr( );

	unique_comptr( const unique_comptr& rhs ) = delete;


	/*
		Operators
	*/
	unique_comptr& operator=( const unique_comptr& rhs ) = delete;
	
	bool operator==( const unique_comptr& rhs );
	
	bool operator!=( const unique_comptr& rhs );
	
	_RawPtrTy** operator&( );
	
	_RawPtrTy* operator->( ) const;

	operator _RawPtrTy*( ) const;


public:
	/*
		Commands
	*/
	// Release and attach the new pointer.
	void Reset( _RawPtrTy* rawPtr );

	// Relese the pointer.
	void Release( );


private:
	_RawPtrTy* m_rawPtr;
};


template<typename _RawPtrTy>
inline void unique_comptr<_RawPtrTy>::Reset( _RawPtrTy* rawPtr )
{
	this->Release( );
	if ( rawPtr )
	{
		rawPtr->AddRef( );
	}
}

template<typename _RawPtrTy>
inline void unique_comptr<_RawPtrTy>::Release( )
{
	if ( m_rawPtr )
	{
		m_rawPtr->Release( );
		m_rawPtr = nullptr;
	}
}

template<typename _RawPtrTy>
inline unique_comptr<_RawPtrTy>::unique_comptr( ) :
	m_rawPtr( nullptr )
{
}

template<typename _RawPtrTy>
inline unique_comptr<_RawPtrTy>::unique_comptr( _RawPtrTy* rhs ) :
	m_rawPtr( rhs )
{
	if ( m_rawPtr )
	{
		m_rawPtr->AddRef( );
	}
}

template<typename _RawPtrTy>
inline unique_comptr<_RawPtrTy>::~unique_comptr( )
{
	if ( m_rawPtr )
	{
		m_rawPtr->Release( );
		m_rawPtr = nullptr;
	}
}

template<typename _RawPtrTy>
inline bool unique_comptr<_RawPtrTy>::operator==( const unique_comptr& rhs )
{
	return ( m_rawPtr == rhs.m_rawPtr );
}

template<typename _RawPtrTy>
inline bool unique_comptr<_RawPtrTy>::operator!=( const unique_comptr & rhs )
{
	return ( m_rawPtr != rhs.m_rawPtr );
}

template<typename _RawPtrTy>
inline _RawPtrTy ** unique_comptr<_RawPtrTy>::operator&( )
{
	return &m_rawPtr;
}

template<typename _RawPtrTy>
inline _RawPtrTy * unique_comptr<_RawPtrTy>::operator->( ) const
{
	return m_rawPtr;
}

template<typename _RawPtrTy>
inline unique_comptr<_RawPtrTy>::operator _RawPtrTy*( ) const
{
	return m_rawPtr;
}


}