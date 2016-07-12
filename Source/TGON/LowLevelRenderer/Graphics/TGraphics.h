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


class TGraphics :
	public GraphicsImpl
{
protected:
	/*
		Cons/Destructor
	*/
	explicit TGraphics( const TWindow& owner );

public:
	virtual ~TGraphics( ) = default;


public:
	/*
		Commands
	*/
	// TGraphics only support the creation as specified type.
	static SpTGraphics Make( const TWindow& owner );

};


inline SpTGraphics TGraphics::Make( 
	const TWindow& owner )
{
	SpTGraphics graphics( new TGraphics( owner ));
	return graphics;
}


}