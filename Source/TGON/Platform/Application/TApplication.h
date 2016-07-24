/*
* Author : Cha Junho
* Date : 04/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Platform/Slate/PlatformApplication.h"


namespace tgon
{


class TGON_API TApplication :
	public ApplicationImpl
{
public:
	static TApplication* Get( )
	{
		static TApplication ret;
		return &ret;
	}

private:
	/*
		Cons/Destructor
	*/
	TApplication( ) = default;

	virtual ~TApplication( ) = default;
};


}