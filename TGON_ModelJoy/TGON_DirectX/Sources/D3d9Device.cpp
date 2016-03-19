#include "stdafx.h"
#include "D3d9Device.h"

#include "GraphicsDeviceProp.h"
#include "D3d9Util.h"


tgon::D3d9Device::D3d9Device( const tgon::SpTWindow& window, const GraphicsDeviceProp& gdcp ) :
	_WndHandle( window->GetWindowHandle( ))
{
	assert( window.get( ) && "Unallocated window passed into D3d9Device." );

	this->SetupDevice( window, gdcp );
	this->SetupSpriteDevice( );
}


tgon::D3d9Device::~D3d9Device( )
{
}


void tgon::D3d9Device::BeginDraw( )
{
	HRESULT result;

	V( GetD3dDevice( )->Clear( 0,
							   NULL,
							   D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
							   D3DCOLOR_ARGB( 255, 0, 0, 255 ),
							   1.0f,
							   0 ));

	V( GetD3dDevice( )->BeginScene( ));
}


void tgon::D3d9Device::EndDraw( )
{
	HRESULT result;
	
	V( GetD3dDevice( )->EndScene( ));
	V( GetD3dDevice( )->Present( NULL, NULL, NULL, NULL ));
}


void VerifyUserEnvironment( /*_Out_ GraphicsDeviceProp* gdcp*/ )
{
	//D3DCAPS9 d3dCaps;
	//GetD3D( )->GetDeviceCaps( D3DADAPTER_DEFAULT,
	//			( d3dCreateParam->gdpt == GraphicsDeviceProcessType::kHardware ) ?
	//				D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//					  &d3dCaps );

	//int32_t vp = 0;
	//vp = ( d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) ?
	//		D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//_D3d->CheckDeviceMultiSampleType( NULL, d3dDeviceType, surfaceFormat, );

	/*D3DDISPLAYMODEEX displayModeEx;
	displayModeEx.RefreshRate = 60;*/ // I think it will be good If using XML
}


HRESULT tgon::D3d9Device::DXUTFindValidDeviceSettings( _Out_ D3D9DeviceSettings* pOut,
													   const D3D9DeviceSettings* pIn,
													   const DXUTMatchOptions* pMatchOptions )
{
	HRESULT result;

	DXUTGetD3D9Enumeration( _WndHandle, _D3d, false );

	D3D9DeviceSettings validDeviceSettings;
	if ( pIn )
	{
		CopyMemory( &validDeviceSettings, pIn, sizeof( D3D9DeviceSettings ));
	}
	else
	{
		memset( &validDeviceSettings, 0, sizeof( D3D9DeviceSettings ));
	}
	
	D3D9DeviceSettings optimalDeviceSettings;
	D3D9DeviceSettings d3d9In = *pIn;
	
	DXUTBuildOptimalD3D9DeviceSettings( &optimalDeviceSettings,
										&d3d9In,
										pMatchOptions );

	result = DXUTFindValidD3D9DeviceSettings( &validDeviceSettings,
									 &d3d9In,
									 pMatchOptions,
									 &optimalDeviceSettings );

	*pOut = validDeviceSettings;

	return result;
}


void tgon::D3d9Device::DXUTBuildOptimalD3D9DeviceSettings( _Out_ D3D9DeviceSettings* pOptimalDeviceSettings,
														   const D3D9DeviceSettings* pDeviceSettingsIn,
														   const DXUTMatchOptions* pMatchOptions )
{
	assert( _D3d != NULL );

	D3DDISPLAYMODE adapterDesktopDisplayMode;

	ZeroMemory( pOptimalDeviceSettings, sizeof( D3D9DeviceSettings ));

	//---------------------
	// Adapter ordinal
	//---------------------    
	if ( pMatchOptions->eAdapterOrdinal == DXUTMT_IGNORE_INPUT )
	{
		pOptimalDeviceSettings->AdapterOrdinal = D3DADAPTER_DEFAULT;
	}
	else
	{
		pOptimalDeviceSettings->AdapterOrdinal = pDeviceSettingsIn->AdapterOrdinal;
	}

	//---------------------
	// Device type
	//---------------------
	if ( pMatchOptions->eDeviceType == DXUTMT_IGNORE_INPUT )
	{
		pOptimalDeviceSettings->DeviceType = D3DDEVTYPE_HAL;
	}
	else
	{
		pOptimalDeviceSettings->DeviceType = pDeviceSettingsIn->DeviceType;
	}

	//---------------------
	// Windowed
	//---------------------
	if ( pMatchOptions->eWindowed == DXUTMT_IGNORE_INPUT )
	{
		pOptimalDeviceSettings->pp.Windowed = TRUE;
	}
	else
	{
		pOptimalDeviceSettings->pp.Windowed = pDeviceSettingsIn->pp.Windowed;
	}

	//---------------------
	// Adapter format
	//---------------------
	if ( pMatchOptions->eAdapterFormat == DXUTMT_IGNORE_INPUT )
	{
		// If windowed, default to the desktop display mode
		// If fullscreen, default to the desktop display mode for quick mode change or 
		// default to D3DFMT_X8R8G8B8 if the desktop display mode is < 32bit
		_D3d->GetAdapterDisplayMode( pOptimalDeviceSettings->AdapterOrdinal, &adapterDesktopDisplayMode );
		if ( pOptimalDeviceSettings->pp.Windowed || D3d9GetColorChannelBits( adapterDesktopDisplayMode.Format ) >=
			 8 )
		{
			pOptimalDeviceSettings->AdapterFormat = adapterDesktopDisplayMode.Format;
		}
		else
		{
			pOptimalDeviceSettings->AdapterFormat = D3DFMT_X8R8G8B8;
		}
	}
	else
	{
		pOptimalDeviceSettings->AdapterFormat = pDeviceSettingsIn->AdapterFormat;
	}

	//---------------------
	// Vertex processing
	//---------------------
	if ( pMatchOptions->eVertexProcessing == DXUTMT_IGNORE_INPUT )
	{
		pOptimalDeviceSettings->BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		pOptimalDeviceSettings->BehaviorFlags = pDeviceSettingsIn->BehaviorFlags;
	}

	//---------------------
	// Resolution
	//---------------------
	if ( pMatchOptions->eResolution == DXUTMT_IGNORE_INPUT )
	{
		// If windowed, default to 640x480
		// If fullscreen, default to the desktop res for quick mode change
		if ( pOptimalDeviceSettings->pp.Windowed )
		{
			pOptimalDeviceSettings->pp.BackBufferWidth = 640;
			pOptimalDeviceSettings->pp.BackBufferHeight = 480;
		}
		else
		{
			_D3d->GetAdapterDisplayMode( pOptimalDeviceSettings->AdapterOrdinal, &adapterDesktopDisplayMode );
			pOptimalDeviceSettings->pp.BackBufferWidth = adapterDesktopDisplayMode.Width;
			pOptimalDeviceSettings->pp.BackBufferHeight = adapterDesktopDisplayMode.Height;
		}
	}
	else
	{
		pOptimalDeviceSettings->pp.BackBufferWidth = pDeviceSettingsIn->pp.BackBufferWidth;
		pOptimalDeviceSettings->pp.BackBufferHeight = pDeviceSettingsIn->pp.BackBufferHeight;
	}

	//---------------------
	// Back buffer format
	//---------------------
	if ( pMatchOptions->eBackBufferFormat == DXUTMT_IGNORE_INPUT )
		pOptimalDeviceSettings->pp.BackBufferFormat = pOptimalDeviceSettings->AdapterFormat; // Default to match the adapter format
	else
		pOptimalDeviceSettings->pp.BackBufferFormat = pDeviceSettingsIn->pp.BackBufferFormat;

	//---------------------
	// Back buffer count
	//---------------------
	if ( pMatchOptions->eBackBufferCount == DXUTMT_IGNORE_INPUT )
		pOptimalDeviceSettings->pp.BackBufferCount = 1; // Default to double buffering.  Causes less latency than triple buffering
	else
		pOptimalDeviceSettings->pp.BackBufferCount = pDeviceSettingsIn->pp.BackBufferCount;

	//---------------------
	// Multisample
	//---------------------
	if ( pMatchOptions->eMultiSample == DXUTMT_IGNORE_INPUT )
	{
		// Default to no multisampling 
		pOptimalDeviceSettings->pp.MultiSampleType = D3DMULTISAMPLE_NONE;
		pOptimalDeviceSettings->pp.MultiSampleQuality = 0;
	}
	else
	{
		pOptimalDeviceSettings->pp.MultiSampleType = pDeviceSettingsIn->pp.MultiSampleType;
		pOptimalDeviceSettings->pp.MultiSampleQuality = pDeviceSettingsIn->pp.MultiSampleQuality;
	}

	//---------------------
	// Swap effect
	//---------------------
	if ( pMatchOptions->eSwapEffect == DXUTMT_IGNORE_INPUT )
		pOptimalDeviceSettings->pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	else
		pOptimalDeviceSettings->pp.SwapEffect = pDeviceSettingsIn->pp.SwapEffect;

	//---------------------
	// Depth stencil 
	//---------------------
	if ( pMatchOptions->eDepthFormat == DXUTMT_IGNORE_INPUT &&
		 pMatchOptions->eStencilFormat == DXUTMT_IGNORE_INPUT )
	{
		UINT nBackBufferBits = D3d9GetColorChannelBits( pOptimalDeviceSettings->pp.BackBufferFormat );
		if ( nBackBufferBits >= 8 )
			pOptimalDeviceSettings->pp.AutoDepthStencilFormat = D3DFMT_D32;
		else
			pOptimalDeviceSettings->pp.AutoDepthStencilFormat = D3DFMT_D16;
	}
	else
	{
		pOptimalDeviceSettings->pp.AutoDepthStencilFormat = pDeviceSettingsIn->pp.AutoDepthStencilFormat;
	}

	//---------------------
	// Present flags
	//---------------------
	if ( pMatchOptions->ePresentFlags == DXUTMT_IGNORE_INPUT )
		pOptimalDeviceSettings->pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	else
		pOptimalDeviceSettings->pp.Flags = pDeviceSettingsIn->pp.Flags;

	//---------------------
	// Refresh rate
	//---------------------
	if ( pMatchOptions->eRefreshRate == DXUTMT_IGNORE_INPUT )
		pOptimalDeviceSettings->pp.FullScreen_RefreshRateInHz = 0;
	else
		pOptimalDeviceSettings->pp.FullScreen_RefreshRateInHz = pDeviceSettingsIn->pp.FullScreen_RefreshRateInHz;

	//---------------------
	// Present interval
	//---------------------
	if ( pMatchOptions->ePresentInterval == DXUTMT_IGNORE_INPUT )
	{
		// For windowed and fullscreen, default to D3DPRESENT_INTERVAL_DEFAULT
		// which will wait for the vertical retrace period to prevent tearing.
		// For benchmarking, use D3DPRESENT_INTERVAL_IMMEDIATE which will
		// will wait not for the vertical retrace period but may introduce tearing.
		pOptimalDeviceSettings->pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	else
	{
		pOptimalDeviceSettings->pp.PresentationInterval = pDeviceSettingsIn->pp.PresentationInterval;
	}
}


HRESULT tgon::D3d9Device::DXUTFindValidD3D9DeviceSettings(
					_Out_  D3D9DeviceSettings* pOut,
					const D3D9DeviceSettings* pIn,
					const DXUTMatchOptions* matchOptions,
					const D3D9DeviceSettings* optimal )
{
	// Find the best combination of:
	//      Adapter Ordinal
	//      Device Type
	//      Adapter Format
	//      Back Buffer Format
	//      Windowed
	// given what's available on the system and the match options combined with the device settings input.
	// This combination of settings is encapsulated bypOptimal the CD3D9EnumDeviceSettingsCombo class.
	float fBestRanking = -1.0f;
	CD3D9EnumDeviceSettingsCombo* pBestDeviceSettingsCombo = NULL;
	D3DDISPLAYMODE adapterDesktopDisplayMode;

	assert( _D3d != NULL );
	CD3D9Enumeration* pd3dEnum = DXUTGetD3D9Enumeration( _WndHandle, _D3d, false );
	std::vector <D3d9AdapterInfo*>* pAdapterList = pd3dEnum->GetAdapterInfoList( );
	for ( int32_t iAdapter = 0; iAdapter < pAdapterList->size( ); iAdapter++ )
	{
		D3d9AdapterInfo* pAdapterInfo = ( *pAdapterList )[iAdapter];

		// Get the desktop display mode of adapter 
		_D3d->GetAdapterDisplayMode( pAdapterInfo->ordinal, &adapterDesktopDisplayMode );

		// Enum all the device types supported by this adapter
		// to find the best device settings
		for ( int32_t iDeviceInfo = 0; iDeviceInfo < pAdapterInfo->deviceInfoList.size( ); iDeviceInfo++ )
		{
			CD3D9EnumDeviceInfo* pDeviceInfo = pAdapterInfo->deviceInfoList[iDeviceInfo];

			// Enum all the device settings combinations.
			// A device settings combination is a unique set of an adapter format,
			// back buffer format, and IsWindowed.
			for ( int32_t iDeviceCombo = 0; iDeviceCombo < pDeviceInfo->deviceSettingsComboList.size( ); iDeviceCombo++ )
			{
				CD3D9EnumDeviceSettingsCombo* pDeviceSettingsCombo = pDeviceInfo->deviceSettingsComboList[iDeviceCombo];

				// If windowed mode the adapter format has to be the same as the desktop 
				// display mode format so skip any that don't match
				if ( pDeviceSettingsCombo->Windowed &&
					 ( pDeviceSettingsCombo->AdapterFormat != adapterDesktopDisplayMode.Format ) )
					continue;

				// Skip any combo that doesn't meet the preserve match options
				if ( false == DXUTDoesD3D9DeviceComboMatchPreserveOptions( pDeviceSettingsCombo, pIn, matchOptions ) )
					continue;

				// Get a ranking number that describes how closely this device combo matches the optimal combo
				float fCurRanking = DXUTRankD3D9DeviceCombo( pDeviceSettingsCombo,
															 optimal, &adapterDesktopDisplayMode );

				// If this combo better matches the input device settings then save it
				if ( fCurRanking > fBestRanking )
				{
					pBestDeviceSettingsCombo = pDeviceSettingsCombo;
					fBestRanking = fCurRanking;
				}
			}
		}
	}

	// If no best device combination was found then fail
	if ( pBestDeviceSettingsCombo == NULL )
		return DXUTERR_NOCOMPATIBLEDEVICES;

	// Using the best device settings combo found, build valid device settings taking heed of 
	// the match options and the input device settings
	D3D9DeviceSettings validDeviceSettings;
	DXUTBuildValidD3D9DeviceSettings( &validDeviceSettings, pBestDeviceSettingsCombo, pIn, matchOptions );
	*pOut = validDeviceSettings;
	
	return S_OK;
}


float tgon::D3d9Device::DXUTRankD3D9DeviceCombo(
	const CD3D9EnumDeviceSettingsCombo* deviceSettingsCombo,
	const D3D9DeviceSettings* optimalDeviceSettings,
	const D3DDISPLAYMODE* adapterDesktopDisplayMode )
{
	float fCurRanking = 0.0f;

	// Arbitrary weights.
	// Gives preference to the ordinal, device type, and windowed
	const float fAdapterOrdinalWeight = 1000.0f;
	const float fDeviceTypeWeight = 100.0f;
	const float fWindowWeight = 10.0f;
	const float fAdapterFormatWeight = 1.0f;
	const float fVertexProcessingWeight = 1.0f;
	const float fResolutionWeight = 1.0f;
	const float fBackBufferFormatWeight = 1.0f;
	const float fMultiSampleWeight = 1.0f;
	const float fDepthStencilWeight = 1.0f;
	const float fRefreshRateWeight = 1.0f;
	const float fPresentIntervalWeight = 1.0f;

	//---------------------
	// Adapter ordinal
	//---------------------
	if ( deviceSettingsCombo->AdapterOrdinal == optimalDeviceSettings->AdapterOrdinal )
	{
		fCurRanking += fAdapterOrdinalWeight;
	}

	//---------------------
	// Device type
	//---------------------
	if ( deviceSettingsCombo->DeviceType == optimalDeviceSettings->DeviceType )
	{
		fCurRanking += fDeviceTypeWeight;
	}
	// Slightly prefer HAL 
	if ( deviceSettingsCombo->DeviceType == D3DDEVTYPE_HAL )
	{
		fCurRanking += 0.1f;
	}

	//---------------------
	// Windowed
	//---------------------
	if ( deviceSettingsCombo->Windowed == optimalDeviceSettings->pp.Windowed )
	{
		fCurRanking += fWindowWeight;
	}

	//---------------------
	// Adapter format
	//---------------------
	if ( deviceSettingsCombo->AdapterFormat == optimalDeviceSettings->AdapterFormat )
	{
		fCurRanking += fAdapterFormatWeight;
	}
	else
	{
		int32_t nBitDepthDelta = abs(( long )D3d9GetColorChannelBits( deviceSettingsCombo->AdapterFormat ) -
								 ( long )D3d9GetColorChannelBits( optimalDeviceSettings->AdapterFormat ));
		float fScale = __max( 0.9f - ( float )nBitDepthDelta * 0.2f, 0.0f );
		fCurRanking += fScale * fAdapterFormatWeight;
	}

	if ( !deviceSettingsCombo->Windowed )
	{
		// Slightly prefer when it matches the desktop format or is D3DFMT_X8R8G8B8
		bool bAdapterOptimalMatch;
		if ( D3d9GetColorChannelBits( adapterDesktopDisplayMode->Format ) >= 8 )
		{
			bAdapterOptimalMatch = ( deviceSettingsCombo->AdapterFormat == adapterDesktopDisplayMode->Format );
		}
		else
		{
			bAdapterOptimalMatch = ( deviceSettingsCombo->AdapterFormat == D3DFMT_X8R8G8B8 );
		}

		if ( bAdapterOptimalMatch )
		{
			fCurRanking += 0.1f;
		}
	}

	//---------------------
	// Vertex processing
	//---------------------
	if (( optimalDeviceSettings->BehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) != 0 ||
		 ( optimalDeviceSettings->BehaviorFlags & D3DCREATE_MIXED_VERTEXPROCESSING ) != 0 )
	{
		if (( deviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) != 0 )
		{
			fCurRanking += fVertexProcessingWeight;
		}
	}
	// Slightly prefer HW T&L
	if (( deviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) != 0 )
	{
		fCurRanking += 0.1f;
	}

	//---------------------
	// Resolution
	//---------------------
	bool bResolutionFound = false;
	for ( int32_t idm = 0; idm < deviceSettingsCombo->pAdapterInfo->displayModeList.size( ); idm++ )
	{
		D3DDISPLAYMODE displayMode = deviceSettingsCombo->pAdapterInfo->displayModeList[idm];
		if ( displayMode.Format != deviceSettingsCombo->AdapterFormat )
		{
			continue;
		}

		if ( displayMode.Width == optimalDeviceSettings->pp.BackBufferWidth &&
			 displayMode.Height == optimalDeviceSettings->pp.BackBufferHeight )
		{
			bResolutionFound = true;
		}
	}
	if ( bResolutionFound )
	{
		fCurRanking += fResolutionWeight;
	}

	//---------------------
	// Back buffer format
	//---------------------
	if ( deviceSettingsCombo->BackBufferFormat == optimalDeviceSettings->pp.BackBufferFormat )
	{
		fCurRanking += fBackBufferFormatWeight;
	}
	else
	{
		int32_t nBitDepthDelta = abs( ( long )D3d9GetColorChannelBits( deviceSettingsCombo->BackBufferFormat ) -
								  ( long )D3d9GetColorChannelBits( optimalDeviceSettings->pp.BackBufferFormat ) );
		float fScale = __max( 0.9f - ( float )nBitDepthDelta * 0.2f, 0.0f );
		fCurRanking += fScale * fBackBufferFormatWeight;
	}

	// Check if this back buffer format is the same as 
	// the adapter format since this is preferred.
	bool bAdapterMatchesBB = ( deviceSettingsCombo->BackBufferFormat == deviceSettingsCombo->AdapterFormat );
	if ( bAdapterMatchesBB )
	{
		fCurRanking += 0.1f;
	}

	//---------------------
	// Back buffer count
	//---------------------
	// No caps for the back buffer count

	//---------------------
	// Multisample
	//---------------------
	bool bMultiSampleFound = false;
	for ( int32_t i = 0; i < deviceSettingsCombo->multiSampleTypeList.size( ); i++ )
	{
		D3DMULTISAMPLE_TYPE msType = deviceSettingsCombo->multiSampleTypeList[i];
		DWORD msQuality = deviceSettingsCombo->multiSampleQualityList[i];

		if ( msType == optimalDeviceSettings->pp.MultiSampleType &&
			 msQuality > optimalDeviceSettings->pp.MultiSampleQuality )
		{
			bMultiSampleFound = true;
			break;
		}
	}
	if ( bMultiSampleFound )
	{
		fCurRanking += fMultiSampleWeight;
	}

	//---------------------
	// Swap effect
	//---------------------
	// No caps for swap effects

	//---------------------
	// Depth stencil 
	//---------------------
	{
		auto findElem = std::find(
				deviceSettingsCombo->depthStencilFormatList.begin(),
				deviceSettingsCombo->depthStencilFormatList.end(),
				optimalDeviceSettings->pp.AutoDepthStencilFormat );
		
		auto notExist = deviceSettingsCombo->depthStencilFormatList.end( );

		if ( findElem != notExist )
		{
			fCurRanking += fDepthStencilWeight;
		}
	}



	//---------------------
	// Present flags
	//---------------------
	// No caps for the present flags

	//---------------------
	// Refresh rate
	//---------------------
	bool bRefreshFound = false;
	for ( int32_t idm = 0; idm < deviceSettingsCombo->pAdapterInfo->displayModeList.size( ); idm++ )
	{
		D3DDISPLAYMODE displayMode = deviceSettingsCombo->pAdapterInfo->displayModeList[idm];
		if ( displayMode.Format != deviceSettingsCombo->AdapterFormat )
		{
			continue;
		}
		if ( displayMode.RefreshRate == optimalDeviceSettings->pp.FullScreen_RefreshRateInHz )
		{
			bRefreshFound = true;
		}
	}
	if ( bRefreshFound )
		fCurRanking += fRefreshRateWeight;

	//---------------------
	// Present interval
	//---------------------
	// If keep present interval then check that the present interval is supported by this combo
	{
		auto findElem = std::find(
				deviceSettingsCombo->presentIntervalList.begin(),
				deviceSettingsCombo->presentIntervalList.end(),
				optimalDeviceSettings->pp.PresentationInterval );
		
		auto notExist = deviceSettingsCombo->presentIntervalList.end( );

		if ( findElem != notExist )
		{
			fCurRanking += fPresentIntervalWeight;
		}
	}

	return fCurRanking;
}


bool tgon::D3d9Device::DXUTDoesD3D9DeviceComboMatchPreserveOptions(
					const CD3D9EnumDeviceSettingsCombo* pDeviceSettingsCombo,
					const D3D9DeviceSettings* pDeviceSettingsIn,
					const DXUTMatchOptions* pMatchOptions )
{
	//---------------------
	// Adapter ordinal
	//---------------------
	if ( pMatchOptions->eAdapterOrdinal == DXUTMT_PRESERVE_INPUT &&
		 ( pDeviceSettingsCombo->AdapterOrdinal != pDeviceSettingsIn->AdapterOrdinal ) )
	{
		return false;
	}

	//---------------------
	// Device type
	//---------------------
	if ( pMatchOptions->eDeviceType == DXUTMT_PRESERVE_INPUT &&
		 ( pDeviceSettingsCombo->DeviceType != pDeviceSettingsIn->DeviceType ) )
	{
		return false;
	}

	//---------------------
	// Windowed
	//---------------------
	if ( pMatchOptions->eWindowed == DXUTMT_PRESERVE_INPUT &&
		 ( pDeviceSettingsCombo->Windowed != pDeviceSettingsIn->pp.Windowed ) )
	{
		return false;
	}

	//---------------------
	// Adapter format
	//---------------------
	if ( pMatchOptions->eAdapterFormat == DXUTMT_PRESERVE_INPUT &&
		 ( pDeviceSettingsCombo->AdapterFormat != pDeviceSettingsIn->AdapterFormat ) )
	{
		return false;
	}

	//---------------------
	// Vertex processing
	//---------------------
	// If keep VP and input has HWVP, then skip if this combo doesn't have HWTL 
	if ( pMatchOptions->eVertexProcessing == DXUTMT_PRESERVE_INPUT &&
		 (( pDeviceSettingsIn->BehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) != 0 ) &&
		 (( pDeviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 ))
	{
		return false;
	}
	
	//---------------------
	// Resolution
	//---------------------
	// If keep resolution then check that width and height supported by this combo
	if ( pMatchOptions->eResolution == DXUTMT_PRESERVE_INPUT )
	{
		bool bFound = false;
		for ( int32_t i = 0; i < pDeviceSettingsCombo->pAdapterInfo->displayModeList.size( ); i++ )
		{
			D3DDISPLAYMODE displayMode = pDeviceSettingsCombo->pAdapterInfo->displayModeList[i];
			if ( displayMode.Format != pDeviceSettingsCombo->AdapterFormat )
			{
				continue; // Skip this display mode if it doesn't match the combo's adapter format
			}

			if ( displayMode.Width == pDeviceSettingsIn->pp.BackBufferWidth &&
				 displayMode.Height == pDeviceSettingsIn->pp.BackBufferHeight )
			{
				bFound = true;
				break;
			}
		}

		// If the width and height are not supported by this combo, return false
		if ( !bFound )
		{
			return false;
		}
	}

	//---------------------
	// Back buffer format
	//---------------------
	if ( pMatchOptions->eBackBufferFormat == DXUTMT_PRESERVE_INPUT &&
		 pDeviceSettingsCombo->BackBufferFormat != pDeviceSettingsIn->pp.BackBufferFormat )
	{
		return false;
	}

	//---------------------
	// Back buffer count
	//---------------------
	// No caps for the back buffer count

	//---------------------
	// Multisample
	//---------------------
	if ( pMatchOptions->eMultiSample == DXUTMT_PRESERVE_INPUT )
	{
		bool bFound = false;
		for ( int32_t i = 0; i < pDeviceSettingsCombo->multiSampleTypeList.size( ); i++ )
		{
			D3DMULTISAMPLE_TYPE msType = pDeviceSettingsCombo->multiSampleTypeList[i];
			DWORD msQuality = pDeviceSettingsCombo->multiSampleQualityList[i];

			if ( msType == pDeviceSettingsIn->pp.MultiSampleType &&
				 msQuality > pDeviceSettingsIn->pp.MultiSampleQuality )
			{
				bFound = true;
				break;
			}
		}

		// If multisample type/quality not supported by this combo, then return false
		if ( !bFound )
		{
			return false;
		}
	}

	//---------------------
	// Swap effect
	//---------------------
	// No caps for swap effects

	//---------------------
	// Depth stencil 
	//---------------------
	// If keep depth stencil format then check that the depth stencil format is supported by this combo
	if ( pMatchOptions->eDepthFormat == DXUTMT_PRESERVE_INPUT &&
		 pMatchOptions->eStencilFormat == DXUTMT_PRESERVE_INPUT )
	{
		if ( pDeviceSettingsIn->pp.AutoDepthStencilFormat != D3DFMT_UNKNOWN )
		{
			auto findElem = std::find(
				pDeviceSettingsCombo->depthStencilFormatList.begin( ),
				pDeviceSettingsCombo->depthStencilFormatList.end( ),
				pDeviceSettingsIn->pp.AutoDepthStencilFormat );

			auto notExist = pDeviceSettingsCombo->depthStencilFormatList.end( );

			if ( findElem == notExist )
			{
				return false;
			}
		}
	}

	// If keep depth format then check that the depth format is supported by this combo
	if ( pMatchOptions->eDepthFormat == DXUTMT_PRESERVE_INPUT &&
		 pDeviceSettingsIn->pp.AutoDepthStencilFormat != D3DFMT_UNKNOWN )
	{
		bool bFound = false;
		UINT dwDepthBits = D3d9GetDepthBits( pDeviceSettingsIn->pp.AutoDepthStencilFormat );
		
		for ( int32_t i = 0; i < pDeviceSettingsCombo->depthStencilFormatList.size( ); i++ )
		{
			D3DFORMAT depthStencilFmt = pDeviceSettingsCombo->depthStencilFormatList[i];
			UINT dwCurDepthBits = D3d9GetDepthBits( depthStencilFmt );
			if ( dwCurDepthBits - dwDepthBits == 0 )
			{
				bFound = true;
			}
		}

		if ( !bFound )
		{
			return false;
		}
	}

	// If keep depth format then check that the depth format is supported by this combo
	if ( pMatchOptions->eStencilFormat == DXUTMT_PRESERVE_INPUT &&
		 pDeviceSettingsIn->pp.AutoDepthStencilFormat != D3DFMT_UNKNOWN )
	{
		bool bFound = false;
		UINT dwStencilBits = D3d9GetStencilBits( pDeviceSettingsIn->pp.AutoDepthStencilFormat );
		
		for ( int32_t i = 0; i < pDeviceSettingsCombo->depthStencilFormatList.size( ); i++ )
		{
			const D3DFORMAT depthStencilFmt = pDeviceSettingsCombo->depthStencilFormatList[i];
			const UINT dwCurStencilBits = D3d9GetStencilBits( depthStencilFmt );
			
			if ( dwCurStencilBits - dwStencilBits == 0 )
			{
				bFound = true;
			}
		}

		if ( !bFound )
			return false;
	}

	//---------------------
	// Present flags
	//---------------------
	// No caps for the present flags

	//---------------------
	// Refresh rate
	//---------------------
	// If keep refresh rate then check that the resolution is supported by this combo
	if ( pMatchOptions->eRefreshRate == DXUTMT_PRESERVE_INPUT )
	{
		bool bFound = false;
		for ( int32_t i = 0; i < pDeviceSettingsCombo->pAdapterInfo->displayModeList.size( ); i++ )
		{
			D3DDISPLAYMODE displayMode = pDeviceSettingsCombo->pAdapterInfo->displayModeList[i];
			if ( displayMode.Format != pDeviceSettingsCombo->AdapterFormat )
				continue;
			if ( displayMode.RefreshRate == pDeviceSettingsIn->pp.FullScreen_RefreshRateInHz )
			{
				bFound = true;
				break;
			}
		}

		// If refresh rate not supported by this combo, then return false
		if ( !bFound )
			return false;
	}

	//---------------------
	// Present interval
	//---------------------
	// If keep present interval then check that the present interval is supported by this combo
	if ( pMatchOptions->ePresentInterval == DXUTMT_PRESERVE_INPUT )
	{
		auto findElem = std::find(
				pDeviceSettingsCombo->presentIntervalList.begin(),
				pDeviceSettingsCombo->presentIntervalList.end(),
				pDeviceSettingsIn->pp.PresentationInterval );
		
		auto notExist = pDeviceSettingsCombo->presentIntervalList.end( );

		if ( findElem == notExist )
		{
			return false;
		}
	}
	return true;
}

void tgon::D3d9Device::SetupDevice( const tgon::SpTWindow& window, const GraphicsDeviceProp& gdcp )
{
	HRESULT result;
	V( Direct3DCreate9Ex( D3D_SDK_VERSION, &_D3d ));

	DXUTMatchOptions matchOptions;
    matchOptions.eAdapterOrdinal = DXUTMT_IGNORE_INPUT;
    matchOptions.eDeviceType = DXUTMT_IGNORE_INPUT;
    matchOptions.eOutput = DXUTMT_IGNORE_INPUT;
    matchOptions.eWindowed = DXUTMT_PRESERVE_INPUT;
    matchOptions.eAdapterFormat = DXUTMT_IGNORE_INPUT;
    matchOptions.eVertexProcessing = DXUTMT_IGNORE_INPUT;
	matchOptions.eResolution = ( gdcp.isWindowed ||
	  ( gdcp.backBufferWidth != 0 && gdcp.backBufferHeight != 0 )) ?
		DXUTMT_CLOSEST_TO_INPUT : DXUTMT_IGNORE_INPUT;
    matchOptions.eBackBufferFormat = DXUTMT_IGNORE_INPUT;
    matchOptions.eBackBufferCount = DXUTMT_IGNORE_INPUT;
    matchOptions.eMultiSample = DXUTMT_IGNORE_INPUT;
    matchOptions.eSwapEffect = DXUTMT_IGNORE_INPUT;
    matchOptions.eDepthFormat = DXUTMT_IGNORE_INPUT;
    matchOptions.eStencilFormat = DXUTMT_IGNORE_INPUT;
    matchOptions.ePresentFlags = DXUTMT_IGNORE_INPUT;
    matchOptions.eRefreshRate = DXUTMT_IGNORE_INPUT;
    matchOptions.ePresentInterval = DXUTMT_IGNORE_INPUT;


	D3D9DeviceSettings deviceSettings = {0};
    deviceSettings.pp.Windowed = ( gdcp.isWindowed ) ? TRUE : FALSE;
    deviceSettings.pp.BackBufferWidth = gdcp.backBufferWidth;
    deviceSettings.pp.BackBufferHeight = gdcp.backBufferHeight;
	deviceSettings.pp.hDeviceWindow = window->GetWindowHandle();

	this->DXUTFindValidDeviceSettings( &deviceSettings, &deviceSettings, &matchOptions );

	V( _D3d->CreateDeviceEx( deviceSettings.AdapterOrdinal,
							  deviceSettings.DeviceType,
							  deviceSettings.pp.hDeviceWindow,
							  deviceSettings.BehaviorFlags,
							  &deviceSettings.pp,
							  NULL,
							  &_D3dDevice ));
}


//--------------------------------------------------------------------------------------
// Builds valid device settings using the match options, the input device settings, and the 
// best device settings combo found.
//--------------------------------------------------------------------------------------
void tgon::D3d9Device::DXUTBuildValidD3D9DeviceSettings( _Out_ D3D9DeviceSettings* pValidDeviceSettings,
														 const CD3D9EnumDeviceSettingsCombo* pBestDeviceSettingsCombo,
														 const D3D9DeviceSettings* pDeviceSettingsIn,
														 const DXUTMatchOptions* pMatchOptions )
{
    assert( _D3d != NULL );
 
	D3DDISPLAYMODE adapterDesktopDisplayMode;
    _D3d->GetAdapterDisplayMode( pBestDeviceSettingsCombo->AdapterOrdinal, &adapterDesktopDisplayMode );

    // For each setting pick the best, taking into account the match options and 
    // what's supported by the device

    //---------------------
    // Adapter Ordinal
    //---------------------
    // Just using pBestDeviceSettingsCombo->AdapterOrdinal

    //---------------------
    // Device Type
    //---------------------
    // Just using pBestDeviceSettingsCombo->DeviceType

    //---------------------
    // Windowed 
    //---------------------
    // Just using pBestDeviceSettingsCombo->Windowed

    //---------------------
    // Adapter Format
    //---------------------
    // Just using pBestDeviceSettingsCombo->AdapterFormat

    //---------------------
    // Vertex processing
    //---------------------
    DWORD dwBestBehaviorFlags = 0;
    if( pMatchOptions->eVertexProcessing == DXUTMT_PRESERVE_INPUT )
    {
        dwBestBehaviorFlags = pDeviceSettingsIn->BehaviorFlags;
    }
    else if( pMatchOptions->eVertexProcessing == DXUTMT_IGNORE_INPUT )
    {
        // The framework defaults to HWVP if available otherwise use SWVP
		if (( pBestDeviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) != 0 )
		{
			dwBestBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
            dwBestBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}
    }
    else // if( pMatchOptions->eVertexProcessing == DXUTMT_CLOSEST_TO_INPUT )    
    {
        // Default to input, and fallback to SWVP if HWVP not available 
        dwBestBehaviorFlags = pDeviceSettingsIn->BehaviorFlags;
        if (( pBestDeviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 &&
            (( dwBestBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) != 0 ||
              ( dwBestBehaviorFlags & D3DCREATE_MIXED_VERTEXPROCESSING ) != 0 ))
        {
            dwBestBehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
            dwBestBehaviorFlags &= ~D3DCREATE_MIXED_VERTEXPROCESSING;
            dwBestBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }

        // One of these must be selected
        if (( dwBestBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING ) == 0 &&
            ( dwBestBehaviorFlags & D3DCREATE_MIXED_VERTEXPROCESSING ) == 0 &&
            ( dwBestBehaviorFlags & D3DCREATE_SOFTWARE_VERTEXPROCESSING ) == 0 )
        {
			if (( pBestDeviceSettingsCombo->pDeviceInfo->Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) != 0 )
			{
				dwBestBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
			}
			else
			{
				dwBestBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			}
        }
    }

    //---------------------
    // Resolution
    //---------------------
    D3DDISPLAYMODE bestDisplayMode;
    if( pMatchOptions->eResolution == DXUTMT_PRESERVE_INPUT )
    {
        bestDisplayMode.Width = pDeviceSettingsIn->pp.BackBufferWidth;
        bestDisplayMode.Height = pDeviceSettingsIn->pp.BackBufferHeight;
    }
    else
    {
        D3DDISPLAYMODE displayModeIn;
        if( pMatchOptions->eResolution == DXUTMT_CLOSEST_TO_INPUT &&
            pDeviceSettingsIn )
        {
            displayModeIn.Width = pDeviceSettingsIn->pp.BackBufferWidth;
            displayModeIn.Height = pDeviceSettingsIn->pp.BackBufferHeight;
        }
        else // if( pMatchOptions->eResolution == DXUTMT_IGNORE_INPUT )   
        {
            if( pBestDeviceSettingsCombo->Windowed )
            {
                // The framework defaults to 640x480 for windowed
                displayModeIn.Width = 640;
                displayModeIn.Height = 480;
            }
            else
            {
                // The framework defaults to desktop resolution for fullscreen to try to avoid slow mode change
                displayModeIn.Width = adapterDesktopDisplayMode.Width;
                displayModeIn.Height = adapterDesktopDisplayMode.Height;
            }
        }

        // Call a helper function to find the closest valid display mode to the optimal 
        DXUTFindValidD3D9Resolution( pBestDeviceSettingsCombo, displayModeIn, &bestDisplayMode );
    }

    //---------------------
    // Back Buffer Format
    //---------------------
    // Just using pBestDeviceSettingsCombo->BackBufferFormat

    //---------------------
    // Back buffer count
    //---------------------
    UINT bestBackBufferCount;
    if( pMatchOptions->eBackBufferCount == DXUTMT_PRESERVE_INPUT )
    {
        bestBackBufferCount = pDeviceSettingsIn->pp.BackBufferCount;
    }
    else if( pMatchOptions->eBackBufferCount == DXUTMT_IGNORE_INPUT )
    {
        // Default to double buffering.  Causes less latency than triple buffering
        bestBackBufferCount = 1;
    }
    else // if( pMatchOptions->eBackBufferCount == DXUTMT_CLOSEST_TO_INPUT )   
    {
        bestBackBufferCount = pDeviceSettingsIn->pp.BackBufferCount;
        if( bestBackBufferCount > 3 )
            bestBackBufferCount = 3;
        if( bestBackBufferCount < 1 )
            bestBackBufferCount = 1;
    }

    //---------------------
    // Multisample
    //---------------------
    D3DMULTISAMPLE_TYPE bestMultiSampleType;
    DWORD bestMultiSampleQuality;
    if( pDeviceSettingsIn && pDeviceSettingsIn->pp.SwapEffect != D3DSWAPEFFECT_DISCARD )
    {
        // Swap effect is not set to discard so multisampling has to off
        bestMultiSampleType = D3DMULTISAMPLE_NONE;
        bestMultiSampleQuality = 0;
    }
    else
    {
        if( pMatchOptions->eMultiSample == DXUTMT_PRESERVE_INPUT )
        {
            bestMultiSampleType = pDeviceSettingsIn->pp.MultiSampleType;
            bestMultiSampleQuality = pDeviceSettingsIn->pp.MultiSampleQuality;
        }
        else if( pMatchOptions->eMultiSample == DXUTMT_IGNORE_INPUT )
        {
            // Default to no multisampling (always supported)
            bestMultiSampleType = D3DMULTISAMPLE_NONE;
            bestMultiSampleQuality = 0;
        }
        else if( pMatchOptions->eMultiSample == DXUTMT_CLOSEST_TO_INPUT )
        {
            // Default to no multisampling (always supported)
            bestMultiSampleType = D3DMULTISAMPLE_NONE;
            bestMultiSampleQuality = 0;

            for( int32_t i = 0; i < pBestDeviceSettingsCombo->multiSampleTypeList.size(); i++ )
            {
                D3DMULTISAMPLE_TYPE type = pBestDeviceSettingsCombo->multiSampleTypeList[i];
                DWORD qualityLevels = pBestDeviceSettingsCombo->multiSampleQualityList[i];

                // Check whether supported type is closer to the input than our current best
                if( abs( type - pDeviceSettingsIn->pp.MultiSampleType ) < abs( bestMultiSampleType -
                                                                               pDeviceSettingsIn->pp.MultiSampleType )
                    )
                {
                    bestMultiSampleType = type;
                    bestMultiSampleQuality = __min( qualityLevels - 1, pDeviceSettingsIn->pp.MultiSampleQuality );
                }
            }
        }
        else
        {
            // Error case
            bestMultiSampleType = D3DMULTISAMPLE_NONE;
            bestMultiSampleQuality = 0;
        }
    }

    //---------------------
    // Swap effect
    //---------------------
    D3DSWAPEFFECT bestSwapEffect;
    if( pMatchOptions->eSwapEffect == DXUTMT_PRESERVE_INPUT )
    {
        bestSwapEffect = pDeviceSettingsIn->pp.SwapEffect;
    }
    else if( pMatchOptions->eSwapEffect == DXUTMT_IGNORE_INPUT )
    {
        bestSwapEffect = D3DSWAPEFFECT_DISCARD;
    }
    else // if( pMatchOptions->eSwapEffect == DXUTMT_CLOSEST_TO_INPUT )   
    {
        bestSwapEffect = pDeviceSettingsIn->pp.SwapEffect;

        // Swap effect has to be one of these 3
        if( bestSwapEffect != D3DSWAPEFFECT_DISCARD &&
            bestSwapEffect != D3DSWAPEFFECT_FLIP &&
            bestSwapEffect != D3DSWAPEFFECT_COPY )
        {
            bestSwapEffect = D3DSWAPEFFECT_DISCARD;
        }
    }

    //---------------------
    // Depth stencil 
    //---------------------
    D3DFORMAT bestDepthStencilFormat;
    bool bestEnableAutoDepthStencil;

    std::vector <int32_t> depthStencilRanking;
    depthStencilRanking.resize( pBestDeviceSettingsCombo->depthStencilFormatList.size() );

    UINT dwBackBufferBitDepth = D3d9GetColorChannelBits( pBestDeviceSettingsCombo->BackBufferFormat );
    UINT dwInputDepthBitDepth = 0;
    if( pDeviceSettingsIn )
        dwInputDepthBitDepth = D3d9GetDepthBits( pDeviceSettingsIn->pp.AutoDepthStencilFormat );

    for( int32_t i = 0; i < pBestDeviceSettingsCombo->depthStencilFormatList.size(); i++ )
    {
        D3DFORMAT curDepthStencilFmt = pBestDeviceSettingsCombo->depthStencilFormatList[i];
        DWORD dwCurDepthBitDepth = D3d9GetDepthBits( curDepthStencilFmt );
        int32_t nRanking;

        if( pMatchOptions->eDepthFormat == DXUTMT_PRESERVE_INPUT )
        {
            // Need to match bit depth of input
            if( dwCurDepthBitDepth == dwInputDepthBitDepth )
                nRanking = 0;
            else
                nRanking = 10000;
        }
        else if( pMatchOptions->eDepthFormat == DXUTMT_IGNORE_INPUT )
        {
            // Prefer match of backbuffer bit depth
            nRanking = abs( ( int32_t )dwCurDepthBitDepth - ( int32_t )dwBackBufferBitDepth * 4 );
        }
        else // if( pMatchOptions->eDepthFormat == DXUTMT_CLOSEST_TO_INPUT )
        {
            // Prefer match of input depth format bit depth
            nRanking = abs( ( int32_t )dwCurDepthBitDepth - ( int32_t )dwInputDepthBitDepth );
        }

        depthStencilRanking.push_back( nRanking );
    }

    UINT dwInputStencilBitDepth = 0;
    if( pDeviceSettingsIn )
        dwInputStencilBitDepth = D3d9GetStencilBits( pDeviceSettingsIn->pp.AutoDepthStencilFormat );

    for( int32_t i = 0; i < pBestDeviceSettingsCombo->depthStencilFormatList.size(); i++ )
    {
        D3DFORMAT curDepthStencilFmt = pBestDeviceSettingsCombo->depthStencilFormatList[i];
        int32_t nRanking = depthStencilRanking[i];
        DWORD dwCurStencilBitDepth = D3d9GetStencilBits( curDepthStencilFmt );

        if( pMatchOptions->eStencilFormat == DXUTMT_PRESERVE_INPUT )
        {
            // Need to match bit depth of input
            if( dwCurStencilBitDepth == dwInputStencilBitDepth )
                nRanking += 0;
            else
                nRanking += 10000;
        }
        else if( pMatchOptions->eStencilFormat == DXUTMT_IGNORE_INPUT )
        {
            // Prefer 0 stencil bit depth
            nRanking += dwCurStencilBitDepth;
        }
        else // if( pMatchOptions->eStencilFormat == DXUTMT_CLOSEST_TO_INPUT )
        {
            // Prefer match of input stencil format bit depth
            nRanking += abs( ( int32_t )dwCurStencilBitDepth - ( int32_t )dwInputStencilBitDepth );
        }

        depthStencilRanking[i] = nRanking;
    }

    int32_t nBestRanking = 100000;
    int32_t nBestIndex = -1;
    for( int32_t i = 0; i < pBestDeviceSettingsCombo->depthStencilFormatList.size(); i++ )
    {
        int32_t nRanking = depthStencilRanking[i];
        if( nRanking < nBestRanking )
        {
            nBestRanking = nRanking;
            nBestIndex = i;
        }
    }

    if( nBestIndex >= 0 )
    {
        bestDepthStencilFormat = pBestDeviceSettingsCombo->depthStencilFormatList[nBestIndex];
        bestEnableAutoDepthStencil = true;
    }
    else
    {
        bestDepthStencilFormat = D3DFMT_UNKNOWN;
        bestEnableAutoDepthStencil = false;
    }


    //---------------------
    // Present flags
    //---------------------
    DWORD dwBestFlags;
    if( pMatchOptions->ePresentFlags == DXUTMT_PRESERVE_INPUT )
    {
        dwBestFlags = pDeviceSettingsIn->pp.Flags;
    }
    else if( pMatchOptions->ePresentFlags == DXUTMT_IGNORE_INPUT )
    {
        dwBestFlags = 0;
        if( bestEnableAutoDepthStencil )
            dwBestFlags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    }
    else // if( pMatchOptions->ePresentFlags == DXUTMT_CLOSEST_TO_INPUT )   
    {
        dwBestFlags = pDeviceSettingsIn->pp.Flags;
        if( bestEnableAutoDepthStencil )
            dwBestFlags |= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    }

    //---------------------
    // Refresh rate
    //---------------------
    if( pBestDeviceSettingsCombo->Windowed )
    {
        // Must be 0 for windowed
        bestDisplayMode.RefreshRate = 0;
    }
    else
    {
        if( pMatchOptions->eRefreshRate == DXUTMT_PRESERVE_INPUT )
        {
            bestDisplayMode.RefreshRate = pDeviceSettingsIn->pp.FullScreen_RefreshRateInHz;
        }
        else
        {
            UINT refreshRateMatch;
            if( pMatchOptions->eRefreshRate == DXUTMT_CLOSEST_TO_INPUT )
            {
                refreshRateMatch = pDeviceSettingsIn->pp.FullScreen_RefreshRateInHz;
            }
            else // if( pMatchOptions->eRefreshRate == DXUTMT_IGNORE_INPUT )   
            {
                refreshRateMatch = adapterDesktopDisplayMode.RefreshRate;
            }

            bestDisplayMode.RefreshRate = 0;

            if( refreshRateMatch != 0 )
            {
                int32_t nBestRefreshRanking = 100000;
                std::vector <D3DDISPLAYMODE>* pDisplayModeList =
                    &pBestDeviceSettingsCombo->pAdapterInfo->displayModeList;
                for( int32_t iDisplayMode = 0; iDisplayMode < pDisplayModeList->size(); iDisplayMode++ )
                {
                    D3DDISPLAYMODE displayMode = ( *pDisplayModeList )[iDisplayMode];
                    if( displayMode.Format != pBestDeviceSettingsCombo->AdapterFormat ||
                        displayMode.Height != bestDisplayMode.Height ||
                        displayMode.Width != bestDisplayMode.Width )
                        continue; // Skip display modes that don't match 

                    // Find the delta between the current refresh rate and the optimal refresh rate 
                    int32_t nCurRanking = abs( ( int32_t )displayMode.RefreshRate - ( int32_t )refreshRateMatch );

                    if( nCurRanking < nBestRefreshRanking )
                    {
                        bestDisplayMode.RefreshRate = displayMode.RefreshRate;
                        nBestRefreshRanking = nCurRanking;

                        // Stop if perfect match found
                        if( nBestRefreshRanking == 0 )
                            break;
                    }
                }
            }
        }
    }

    //---------------------
    // Present interval
    //---------------------
    UINT bestPresentInterval;
    if( pMatchOptions->ePresentInterval == DXUTMT_PRESERVE_INPUT )
    {
        bestPresentInterval = pDeviceSettingsIn->pp.PresentationInterval;
    }
    else if( pMatchOptions->ePresentInterval == DXUTMT_IGNORE_INPUT )
    {
        // For windowed and fullscreen, default to D3DPRESENT_INTERVAL_DEFAULT
        // which will wait for the vertical retrace period to prevent tearing.
        // For benchmarking, use D3DPRESENT_INTERVAL_DEFAULT  which will
        // will wait not for the vertical retrace period but may introduce tearing.
        bestPresentInterval = D3DPRESENT_INTERVAL_DEFAULT;
    }
    else // if( pMatchOptions->ePresentInterval == DXUTMT_CLOSEST_TO_INPUT )   
    {
		auto findElem = std::find(
				pBestDeviceSettingsCombo->presentIntervalList.begin(),
				pBestDeviceSettingsCombo->presentIntervalList.end(),
				pDeviceSettingsIn->pp.PresentationInterval );
		
		auto notExist = pBestDeviceSettingsCombo->presentIntervalList.end( );

        if ( findElem != notExist )
        {
            bestPresentInterval = pDeviceSettingsIn->pp.PresentationInterval;
        }
        else
        {
            bestPresentInterval = D3DPRESENT_INTERVAL_DEFAULT;
        }
    }

    // Fill the device settings struct
    ZeroMemory( pValidDeviceSettings, sizeof( D3D9DeviceSettings ) );
    pValidDeviceSettings->AdapterOrdinal = pBestDeviceSettingsCombo->AdapterOrdinal;
    pValidDeviceSettings->DeviceType = pBestDeviceSettingsCombo->DeviceType;
    pValidDeviceSettings->AdapterFormat = pBestDeviceSettingsCombo->AdapterFormat;
    pValidDeviceSettings->BehaviorFlags = dwBestBehaviorFlags;
    pValidDeviceSettings->pp.BackBufferWidth = bestDisplayMode.Width;
    pValidDeviceSettings->pp.BackBufferHeight = bestDisplayMode.Height;
    pValidDeviceSettings->pp.BackBufferFormat = pBestDeviceSettingsCombo->BackBufferFormat;
    pValidDeviceSettings->pp.BackBufferCount = bestBackBufferCount;
    pValidDeviceSettings->pp.MultiSampleType = bestMultiSampleType;
    pValidDeviceSettings->pp.MultiSampleQuality = bestMultiSampleQuality;
    pValidDeviceSettings->pp.SwapEffect = bestSwapEffect;
	pValidDeviceSettings->pp.hDeviceWindow = pDeviceSettingsIn->pp.hDeviceWindow;
    pValidDeviceSettings->pp.Windowed = pBestDeviceSettingsCombo->Windowed;
    pValidDeviceSettings->pp.EnableAutoDepthStencil = bestEnableAutoDepthStencil;
    pValidDeviceSettings->pp.AutoDepthStencilFormat = bestDepthStencilFormat;
    pValidDeviceSettings->pp.Flags = dwBestFlags;
    pValidDeviceSettings->pp.FullScreen_RefreshRateInHz = bestDisplayMode.RefreshRate;
    pValidDeviceSettings->pp.PresentationInterval = bestPresentInterval;
}

HRESULT tgon::D3d9Device::DXUTFindValidD3D9Resolution(
					const CD3D9EnumDeviceSettingsCombo* pBestDeviceSettingsCombo,
					const D3DDISPLAYMODE displayModeIn,
					_Out_ D3DDISPLAYMODE* pBestDisplayMode )
{
	D3DDISPLAYMODE bestDisplayMode;
	ZeroMemory( &bestDisplayMode, sizeof( D3DDISPLAYMODE ) );

	if ( pBestDeviceSettingsCombo->Windowed )
	{
		// In windowed mode, all resolutions are valid but restritions still apply 
		// on the size of the window.  See DXUTChangeD3D9Device() for details
		*pBestDisplayMode = displayModeIn;
	}
	else
	{
		int32_t nBestRanking = 100000;
		int32_t nCurRanking;
		std::vector<D3DDISPLAYMODE>* pDisplayModeList = &pBestDeviceSettingsCombo->pAdapterInfo->displayModeList;
		for ( int32_t iDisplayMode = 0; iDisplayMode < pDisplayModeList->size( ); iDisplayMode++ )
		{
			D3DDISPLAYMODE displayMode = ( *pDisplayModeList )[iDisplayMode];

			// Skip display modes that don't match the combo's adapter format
			if ( displayMode.Format != pBestDeviceSettingsCombo->AdapterFormat )
				continue;

			// Find the delta between the current width/height and the optimal width/height
			nCurRanking = abs( ( int32_t )displayMode.Width - ( int32_t )displayModeIn.Width ) +
				abs( ( int32_t )displayMode.Height - ( int32_t )displayModeIn.Height );

			if ( nCurRanking < nBestRanking )
			{
				bestDisplayMode = displayMode;
				nBestRanking = nCurRanking;

				// Stop if perfect match found
				if ( nBestRanking == 0 )
					break;
			}
		}

		if ( bestDisplayMode.Width == 0 )
		{
			*pBestDisplayMode = displayModeIn;
			return E_FAIL; // No valid display modes found
		}

		*pBestDisplayMode = bestDisplayMode;
	}

	return S_OK;
}

void tgon::D3d9Device::SetupSpriteDevice( )
{
	HRESULT result;
	V( D3DXCreateSprite( _D3dDevice, &_D3dSprite ));
}
