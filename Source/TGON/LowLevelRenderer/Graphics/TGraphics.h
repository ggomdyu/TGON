/*
* Author : Junho-Cha
* Date : 01/08/2016
* Latest author :
* Latest date : 
*/

#pragma once
#include "../Platform/Slate/PlatformGraphics.h"
#include "../Platform/Slate/PlatformFwd.h"


namespace tgon
{


using SpTGraphics = std::shared_ptr<class TGraphics>;
using WpTGraphics = std::weak_ptr<class TGraphics>;

class TGraphics : public GraphicsImpl
{
public:
	static SpTGraphics Create( const SpTWindow&, const struct GraphicsStyle& );
	virtual ~TGraphics( );

private:
	explicit TGraphics( const SpTWindow&, const struct GraphicsStyle& );
};


inline SpTGraphics tgon::TGraphics::Create(
	const SpTWindow& window,
	const GraphicsStyle& grpStyle )
{
	SpTGraphics grp( new TGraphics( window, grpStyle ));
	return grp;
}


}