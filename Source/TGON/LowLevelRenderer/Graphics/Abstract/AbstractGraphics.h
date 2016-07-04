/*
* Author : Junho-Cha
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Platform/Config/Build.h"
#include "../../../Platform/Window/TWindow.h"


namespace tgon
{


class TGON_API AbstractGraphics : 
	boost::noncopyable
{
protected:
	AbstractGraphics( ) = default;
	
public:
	virtual ~AbstractGraphics( ) = 0 {}

	explicit AbstractGraphics( const AbstractGraphics& ) = delete;

	AbstractGraphics& operator=( const AbstractGraphics& ) = delete;

public:
	// Begin scene rendering. Return true if device can render.
	virtual bool BeginScene( ) = 0;

	// End scene rendering. This function must be called after BeginScene
	virtual void EndScene( ) = 0;
};


}