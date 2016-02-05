/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include <string>
#include "..\..\ThirdParty\TinyXML2\tinyxml2.h"


namespace tinyxml2
{

	/* 
		Breadth search
	*/
	XMLElement* FindSiblingElementFromParent( const std::string& rNodeName,
														XMLElement* pParent );

	/*
		Depth search
	*/
	XMLElement* FindElementFromParent( const std::string& rNodeName,
													_In_ XMLElement* pParent );

	XMLElement* FindElementFromRoot( const std::string& rNodeName,
										_In_ XMLDocument& rDocument );

}