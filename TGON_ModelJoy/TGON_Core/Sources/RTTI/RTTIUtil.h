/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-17
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "RTTI.h"

namespace tgon
{
	bool DynamicCast( const RTTI* from, const RTTI* to );

	template <typename _To, typename _From>
	bool DynamicCast( const _From& from );
}