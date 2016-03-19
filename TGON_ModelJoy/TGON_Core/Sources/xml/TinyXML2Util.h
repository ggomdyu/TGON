/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-28
* ���� ���� :
* ���� ������ :
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