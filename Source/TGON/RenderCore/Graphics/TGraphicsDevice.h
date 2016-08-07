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


class TGraphicsDevice;
using SpTGraphicsDevice = std::shared_ptr<TGraphicsDevice>;

class TGON_API TGraphicsDevice :
	public GraphicsDeviceImpl
{
	/*
		Cons/Destructor
	*/
protected:
	//
	// Constructor
	//
	// @param deviceWindow Set window which want to present 3D space
	// @param graphicsProp Set graphics device property ( Describe Enable toggle full-screen, depth buffer bits, ... )
	//
	explicit TGraphicsDevice( /*In*/ TWindow* deviceWindow, /*In*/ const GraphicsProperty& grpProp );

public:
	//
	// Destructor
	//
	virtual ~TGraphicsDevice( ) = default;


public:
	/*
		Commands
	*/
	//
	// TGraphics only support the creation as specified type.
	//
	// @param deviceWindow Set window which want to present 3D space
	// @param graphicsProp Set graphics device property ( Describe Enable toggle full-screen, depth buffer bits, ... )
	//
	// @return Return the reference counting smart pointer type( = std::shared_ptr ) of this class.
	//
	static SpTGraphicsDevice Make( /*In*/ TWindow* deviceWindow, /*In*/ const GraphicsProperty& graphicsProp );

};


inline SpTGraphicsDevice TGraphicsDevice::Make( TWindow* deviceWindow, const GraphicsProperty& grpProp )
{
	SpTGraphicsDevice graphics( new TGraphicsDevice( deviceWindow, grpProp ));
	return graphics;
}


}