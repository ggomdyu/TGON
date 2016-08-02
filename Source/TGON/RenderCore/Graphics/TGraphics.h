/*
* Author : Cha Junho
* Date : 01/08/2016
* Latest author :
* Latest date : 
*/


#pragma once
#include "../Slate/PlatformGraphics.h"


namespace tgon
{


class TGraphics;
using SpTGraphics = std::shared_ptr<TGraphics>;

class TGON_API TGraphics :
	public GraphicsImpl
{
protected:
	/*
		Cons/Destructor
	*/
	explicit TGraphics( TWindow* deviceWindow, bool isWindowed );

public:
	virtual ~TGraphics( ) = default;


public:
	/*
		Commands
	*/
	// TGraphics only support the creation as specified type.
	static SpTGraphics Make( TWindow* deviceWindow, bool isWindowed );

};

inline SpTGraphics TGraphics::Make( 
	TWindow* deviceWindow, 
	bool isWindowed )
{
	SpTGraphics graphics( new TGraphics( deviceWindow, isWindowed ));
	return graphics;
}


}