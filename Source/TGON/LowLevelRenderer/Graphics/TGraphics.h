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
	explicit TGraphics( const TWindow& owner );

public:
	// TGraphics only support the creation as specified type.
	static SpTGraphics Make( const TWindow& owner );

	virtual ~TGraphics( ) = default;
};


}


inline tgon::SpTGraphics tgon::TGraphics::Make( 
	const TWindow& owner )
{
	SpTGraphics ret( new TGraphics( owner ));
	return ret;
}