/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author : 
* Latest date : 
*/

#pragma once
#include "../Object/TEventSubject.h"
#include "../../Platform/Window/TWindow.h"


namespace tgon
{


using SpTEventWindow = std::shared_ptr<class TEventWindow>;

class TGON_API TEventWindow :
	public TWindow,
	public TEventSubject
{
public:
	TGON_OBJECT( TEventWindow, TEventSubject )


protected:
	/*
		Cons/Destructor
	*/
	explicit TEventWindow( const WindowStyle& wndStyle );

public:
	virtual ~TEventWindow( ) = default;


public:
	/*
		Commands
	*/
	// TWindow only support the creation as specified type.
	static SpTEventWindow Make( const WindowStyle& );

};
//
//
//inline SpTWindow TWindow::Make( const WindowStyle& wndStyle )
//{
//	SpTWindow window( new TWindow( wndStyle ));
//	return window;
//}


}