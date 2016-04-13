/*
* Author : Taewoo-Kim
* Date : 2015-04-26
* Latest author : Junho-Cha
* Latest date : 2016-01-17
*/


#pragma once
#include "Layered/IGraphicsDevice.h"
#include "../Config/Platform/PlatformFwd.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "D3d9Fwd.h"


namespace tgon
{

struct D3d9DeviceImpl
{
	SpD3d9Ex d3d;
	SpD3d9DeviceEx d3dDevice;
	SpD3d9Sprite d3dSprite;

	D3DCAPS9 deviceCaps;
};




class D3d9Device;
typedef D3d9Device GraphicsDeviceImpl;

class D3d9Device : private IGraphicsDeviceInterface
{
	/*
		@ Cons/Destructors
	*/
protected:
	explicit D3d9Device( const SpTWindow& window,
						 const struct GraphicsDeviceProp& gdcp );
public:
	virtual ~D3d9Device( );

	D3d9Device( const D3d9Device& ) = delete;
	D3d9Device& operator=( const D3d9Device& ) = delete;


	/*
		@ Commands
	*/
public:
	virtual void BeginDraw( ) override;
	virtual void EndDraw( ) override;

	
	/*
		@ Internal work
	*/
private:
	void SetupDevice( const tgon::SpTWindow& window,
					  const GraphicsDeviceProp& gdcp );
	void SetupSpriteDevice( );

	/*
		@ Protected data area
	*/
private:
	D3d9DeviceImpl m_devImpl;
};

}