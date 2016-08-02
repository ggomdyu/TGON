/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author : 
* Latest date : 
*/

#pragma once
#include "../../Platform/Slate/PlatformWindow.h"


namespace tgon
{


class TWindow;
using SpTWindow = std::shared_ptr<TWindow>;

class TGON_API TWindow :
	public WindowImpl
{
public:
	/*
		Cons/Destructor
	*/
	explicit TWindow( const WindowStyle& wndStyle );

	virtual ~TWindow( ) = default;
};


}