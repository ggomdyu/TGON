/*
* Author : Cha Junho
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Platform/Config/Build.h"

#include <cstdint>


namespace tgon
{

class AbstractGraphicsDeviceEventHandler
{
	/*
		Cons/Destructor
	*/
public:
	AbstractGraphicsDeviceEventHandler( ) = default;

	virtual ~AbstractGraphicsDeviceEventHandler( ) = default;


	/*
		Event handlers
	*/
public:
	// Use only DirectX
	virtual void OnDeviceLost( ) {}

	// Use only DirectX
	virtual void OnDeviceReset( ) {}

	//
	// Screen resize event handler
	//
	// @param width is resized window width
	// @param height is resized window height
	//
	virtual void OnScreenResize( uint32_t width, uint32_t height ) {}

};

}
