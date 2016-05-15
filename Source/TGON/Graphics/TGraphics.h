/*
* Author : Junho-Cha
* Date : 01/08/2016
* Latest author :
* Latest date : 
* Description : Platform selected graphics type
*/

#pragma once
#include "../Platform/PlatformGraphics.h"
#include "../Platform/PlatformFwd.h"


namespace tgon
{


class TGraphics;
using SpTGraphics = std::shared_ptr<TGraphics>;
using WpTGraphics = std::weak_ptr<TGraphics>;


class TGraphics : public GraphicsImpl
{
public:
	static SpTGraphics Create(
		const SpTWindow&, 
		const struct GraphicsStyle& );

private:
	explicit TGraphics( 
		const SpTWindow&, 
		const struct GraphicsStyle& );
public:
	virtual ~TGraphics( );
};


inline SpTGraphics tgon::TGraphics::Create(
	const SpTWindow& window,
	const GraphicsStyle& grpStyle )
{
	SpTGraphics grp( new TGraphics( window, grpStyle ));
	return grp;
}


}