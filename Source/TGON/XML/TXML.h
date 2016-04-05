/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <tinyxml2_wchar_t.h>

namespace tgon
{
	/* 
		Breadth node search
	*/
	tinyxml2::XMLElement* FindElementFromParent(
			const wchar_t* const nodeName,
			tinyxml2::XMLElement* const parentNode
		);
}