#pragma once

namespace tgon
{


struct D3dDeviceCreateParam : public GraphicsDeviceCreateParam
{
	virtual ~D3dDeviceCreateParam( ) {}

	bool isFullWindow;
	GraphicsDeviceProcessType gdpt;
	DWORD d3dBehaviorFlag;
};


}