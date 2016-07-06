/*
* Author : Junho-Cha
* Date : 07/06/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IComparable
{
public:
	void CompareTo( class TObject* );
	void CompareTo( class TObject& ) = 0;
}


}

inline void tgon::IComparable( class TObject* obj )
{
	this->CompareTo( *obj );
}