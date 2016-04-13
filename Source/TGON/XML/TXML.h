/*
* Author : Junho-Cha
* Date : 2016-01-28
* Latest author :
* Latest date :
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