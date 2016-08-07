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


class TWindow;

class TGON_API TApplication :
	public ApplicationImpl
{
/*
	Gets
*/
	// 
	// TApplication singleton interface
	// 
	// @return Return Global TApplication instance
	// 
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

private:
	//std::map<std::string, TWindow*> m_windows;
};


}