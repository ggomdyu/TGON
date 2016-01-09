/*
* 작성자 : 차준호
* 작성일 : 2015-12-28
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <functional>
#include <vector>

//
//namespace tgon {
//	template <typename T> class delegate;
//
//	template<class R, class ...A>
//	class delegate<R( A... )>
//	{
//		using func_type = std::function<R( )>;
//
//	public:
//		delegate( )												{ }
//		delegate( func_type arg )							{ this->push_back( arg ); }
//		delegate( func_type&& arg )						{ this->emplace_back( std::move( arg )); }
//		~delegate( )												{ }
//
//		delegate& operator+=( func_type rhs )			{ this->push_back( rhs ); return *this; }
//		delegate& operator=( func_type rhs )			{ clear( ); this->push_back( rhs ); return *this; };
//		delegate& operator=( const delegate& rhs )	{ if ( this == rhs ) return *this; m_repo = rhs.m_repo; };
//		void operator()( )										{ for ( auto& func : m_repo ) func( ); }
//
//	public:
//		void push_back( func_type arg )					{ m_repo.push_back( arg ); }
//		void emplace_back( func_type&& arg )			{ m_repo.emplace_back( std::move( arg )); }
//
//		int size( ) const											{ m_repo.size( ); }
//
//	private:
//		std::vector<func_type> m_repo;
//	};
//}