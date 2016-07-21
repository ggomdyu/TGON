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


using SpTGraphics = std::shared_ptr<class TGraphics>;

class TGON_API TGraphics :
	public GraphicsImpl
{
protected:
	/*
		Cons/Destructor
	*/
	explicit TGraphics( class TWindow* deviceWindow );

public:
	virtual ~TGraphics( ) = default;


public:
	/*
		Commands
	*/
	// TGraphics only support the creation as specified type.
	static SpTGraphics Make( class TWindow* deviceWindow );

};

inline SpTGraphics TGraphics::Make( 
	class TWindow* deviceWindow )
{
	SpTGraphics graphics( new TGraphics( deviceWindow ));
	return graphics;
}


}