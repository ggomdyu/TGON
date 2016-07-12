/*
* Author : Cha Junho
* Date : 07/06/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Config/Build.h"
#include "TObject.h"


namespace tgon
{

class IComparable
{
public:
	virtual void CompareTo( const TObject& ) = 0;
};


}