/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include <string>
#include "tinyxml2.h"


namespace tinyxml2
{

	/* 
		Breadth search
	*/
	XMLElement* FindSiblingElementFromParent( const std::string& nodeName,
														XMLElement* parent );

	/*
		Depth search
	*/
	XMLElement* FindElementFromParent( const std::string& nodeName,
													_In_ XMLElement* parent );

	XMLElement* FindElementFromRoot( const std::string& nodeName,
										_In_ XMLDocument& document );

}