/*
* 작성자 : 김태우
* 작성일 : 2015-04-26
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-17
*/


#pragma once
#include "IGraphicsDevice.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <atlbase.h>
#include <Windows.h>

#include "TWindow.h"
#include "D3d9Type.h"
#include "D3d9Enum.h"


//--------------------------------------------------------------------------------------
// Error codes
//--------------------------------------------------------------------------------------
#define DXUTERR_NODIRECT3D              MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0901)
#define DXUTERR_NOCOMPATIBLEDEVICES     MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0902)
#define DXUTERR_MEDIANOTFOUND           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0903)
#define DXUTERR_NONZEROREFCOUNT         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0904)
#define DXUTERR_CREATINGDEVICE          MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0905)
#define DXUTERR_RESETTINGDEVICE         MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0906)
#define DXUTERR_CREATINGDEVICEOBJECTS   MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0907)
#define DXUTERR_RESETTINGDEVICEOBJECTS  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0908)
#define DXUTERR_DEVICEREMOVED           MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x090A)


namespace tgon
{


class D3d9Device;
typedef D3d9Device GraphicsDeviceImpl;


class D3d9Device : private IGraphicsDeviceInterface
{
	/*
		@ Constructors or Destructors
	*/
protected:
	explicit D3d9Device( const SpTWindow& window,
						 const struct GraphicsDeviceProp& gdcp );
public:
	D3d9Device( const D3d9Device& ) = delete;
	virtual ~D3d9Device( );

	D3d9Device& operator=( const D3d9Device& ) = delete;


	/*
		@ GraphicsDevice commands
	*/
public:
	virtual void BeginDraw( ) override;
	virtual void EndDraw( ) override;

	const SpD3d9Ex& GetD3D( ) { return _D3d; }
	const SpD3d9DeviceEx& GetD3dDevice( ) { return _D3dDevice; }
	const SpD3d9Sprite& GetD3dSprite( ) { return _D3dSprite; }


	/*
		@ Internal work
	*/
private:
	void SetupDevice( const tgon::SpTWindow& window,
					  const GraphicsDeviceProp& gdcp );
	void SetupSpriteDevice( );

	/*
		This function tries to find valid device settings based upon the input device settings 
		struct and the match options. For each device setting a match option in the 
		DXUTMatchOptions struct specifies how the function makes decisions.  For example, if 
		the caller wants a HAL device with a back buffer format of D3DFMT_A2B10G10R10 but the 
		HAL device on the system does not support D3DFMT_A2B10G10R10 however a REF device is 
		installed that does, then the function has a choice to either use REF or to change to 
		a back buffer format to compatible with the HAL device.  The match options lets the 
		caller control how these choices are made.
		
		Each match option must be one of the following types: 
		DXUTMT_IGNORE_INPUT: Uses the closest valid value to a default 
		DXUTMT_PRESERVE_INPUT: Uses the input without change, but may cause no valid device to be found
		DXUTMT_CLOSEST_TO_INPUT: Uses the closest valid value to the input 
		
		If pMatchOptions is NULL then, all of the match options are assumed to be DXUTMT_IGNORE_INPUT.  
		The function returns failure if no valid device settings can be found otherwise 
		the function returns success and the valid device settings are written to pOut.
	*/
	HRESULT DXUTFindValidDeviceSettings( _Out_ D3D9DeviceSettings* out,
										 const D3D9DeviceSettings* in,
										 const DXUTMatchOptions* matchOptions );

	/*
		Internal helper function to build a D3D9 device settings structure based upon the match 
		options.  If the match option is set to ignore, then a optimal default value is used.
		The default value may not exist on the system, but later this will be taken 
		into account.
	*/
	void DXUTBuildOptimalD3D9DeviceSettings( _Out_ D3D9DeviceSettings* optimalDeviceSettings,
											 const D3D9DeviceSettings* deviceSettingsIn,
											 const DXUTMatchOptions* matchOptions );

	/*
		Builds valid device settings using the match options, the input device settings, and the 
		best device settings combo found.
	*/
	void DXUTBuildValidD3D9DeviceSettings( _Out_ D3D9DeviceSettings* validDeviceSettings,
										   const CD3D9EnumDeviceSettingsCombo* bestDeviceSettingsCombo,
										   const D3D9DeviceSettings* deviceSettingsIn,
										   const DXUTMatchOptions* matchOptions );

	HRESULT DXUTFindValidD3D9DeviceSettings( _Out_ D3D9DeviceSettings* out,
											 const D3D9DeviceSettings* in,
											 const DXUTMatchOptions* matchOptions,
											 const D3D9DeviceSettings* optimal );

	/*
		Returns false for any CD3D9EnumDeviceSettingsCombo that doesn't meet the preserve 
		match options against the input pDeviceSettingsIn.
	*/
	bool DXUTDoesD3D9DeviceComboMatchPreserveOptions( const CD3D9EnumDeviceSettingsCombo* deviceSettingsCombo,
													  const D3D9DeviceSettings* deviceSettingsIn,
													  const DXUTMatchOptions* matchOptions );

	/*
		Returns a ranking number that describes how closely this device 
		combo matches the optimal combo based on the match options and the optimal device settings
	*/
	float DXUTRankD3D9DeviceCombo( const CD3D9EnumDeviceSettingsCombo* deviceSettingsCombo,
								   const D3D9DeviceSettings* optimalDeviceSettings,
								   const D3DDISPLAYMODE* adapterDesktopDisplayMode );

	/*
		Internal helper function to find the closest allowed display mode to the optimal 
	*/
	HRESULT DXUTFindValidD3D9Resolution( const CD3D9EnumDeviceSettingsCombo* bestDeviceSettingsCombo,
										 const D3DDISPLAYMODE displayModeIn,
										 _Out_ D3DDISPLAYMODE* bestDisplayMode );


	/*
		@ Protected data area
	*/
private:
	SpD3d9Ex		_D3d;
	SpD3d9DeviceEx	_D3dDevice;
	SpD3d9Sprite	_D3dSprite;

	const HWND		_WndHandle;

	////D3DXMATRIXA16 m_matWorld;
	//D3DXMATRIXA16 m_matView, m_matProj;
	//D3DXVECTOR3 m_eye, m_lookAt, m_up;
	//D3DXVECTOR3 m_vView, m_vCross;
};


}