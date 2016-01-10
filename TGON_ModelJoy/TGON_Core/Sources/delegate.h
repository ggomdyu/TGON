/*
* 작성자 : 차준호
* 작성일 : 2015-12-28
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-10
*/

#pragma once
#include <cassert>

namespace tgon
{


template <typename T> class delegate;

template<class _Ret, class ..._Args>
class delegate<_Ret( _Args... )>
{
	using _DelFunc = _Ret(*)( _Args... );

public:
	delegate( _DelFunc func = nullptr )		{ m_delFunc = func; }
		
	delegate&	operator=( _DelFunc func )				{ m_delFunc = func; return *this; }
	bool			operator==( const delegate& rhs )	{ return ( m_delFunc == rhs.m_delFunc ); }
	bool			operator!=( const delegate& rhs )		{ return ( m_delFunc != rhs.m_delFunc ); }
	_Ret			operator()( _Args... args )					{ return Invoke( args... ); }

public:
	_Ret Invoke( _Args... args )
	{
		assert( m_delFunc && "A delegate used on uninitialized state." );
		return m_delFunc( args... );
	}

private:
	_DelFunc m_delFunc;
};


}