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


using SpTWindow = std::shared_ptr<class TWindow>;

class TGON_API TWindow :
	public WindowImpl
{
protected:
	/*
		Cons/Destructor
	*/
	explicit TWindow( const WindowStyle& wndStyle );

public:
	virtual ~TWindow( ) = default;


public:
	/*
		Commands
	*/
	// TWindow only support the creation as specified type.
	static SpTWindow Make( const WindowStyle& );

};


inline SpTWindow TWindow::Make( const WindowStyle& wndStyle )
{
	SpTWindow window( new TWindow( wndStyle ));
	return window;
}


}