/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-28
* ���� ���� :
* ���� ������ :
*/


#pragma once


/* DO NOT CHANGE this namespace keyword to std !!! */

namespace tgon 
{
	inline bool atob( const char* _Str )
	{	// convert string to bool
		const char *_Ptr = _Str;
		bool _Ans = ( _Str[0] != '0' );

		return ( _Ans );
	}
}
