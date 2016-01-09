#include "RTTIUtil.h"

template <typename _To, typename _From>
bool tgon::DynamicCast( const _From& from )
{
	typedef std::remove_pointer<_From>::type _Fromrp;
	typedef std::remove_pointer<_To>::type _Torp;

	static_assert( std::is_pointer<_From>::value, "The arguments must be a pointer or referenced to a complete class." );
	static_assert( std::is_class<_Fromrp>::value, "The arguments must be complete class type, no default type." );
	static_assert( std::is_pointer<_To>::value, "The type in DynamicCast must be a pointer." );

	return DynamicCast( from->GetRTTI( ), RTTI::GetRTTI<_Torp>( ));
}