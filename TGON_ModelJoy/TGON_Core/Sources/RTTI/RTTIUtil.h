/*
* 작성자 : 차준호
* 작성일 : 2015-12-17
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "RTTI.h"

namespace tgon
{
	bool DynamicCast( const RTTI* from, const RTTI* to );

	template <typename _To, typename _From>
	bool DynamicCast( const _From& from );
}