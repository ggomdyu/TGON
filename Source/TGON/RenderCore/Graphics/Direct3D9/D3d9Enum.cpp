#include "PrecompiledHeader.h"
#include "D3d9Enum.h"


////======================================================================================
////======================================================================================
//// Direct3D 9 section
////======================================================================================
////======================================================================================
//std::shared_ptr<CD3D9Enumeration> g_pDXUTD3D9Enumeration;
//
//
//HRESULT WINAPI DXUTCreateD3D9Enumeration( )
//{
//	if ( g_pDXUTD3D9Enumeration == NULL )
//	{
//		g_pDXUTD3D9Enumeration.reset( new CD3D9Enumeration( ));
//		if ( NULL == g_pDXUTD3D9Enumeration )
//			return E_OUTOFMEMORY;
//	}
//	return S_OK;
//}
//
//CD3D9Enumeration* DXUTGetD3D9Enumeration(
//			HWND focusWindow,
//			IDirect3D9Ex* d3dInterface,
//			bool bForceEnumerate )
//{
//	class DXUTMemoryHelperD3D9Enum
//	{
//	public:
//		DXUTMemoryHelperD3D9Enum( ) {
//			DXUTCreateD3D9Enumeration( );
//		}
//	};
//
//    // Using an static class with accessor function to allow control of the construction order
//    static DXUTMemoryHelperD3D9Enum d3d9enumMemory;
//
//    if( g_pDXUTD3D9Enumeration && ( !g_pDXUTD3D9Enumeration->HasEnumerated() || bForceEnumerate ) )
//    {
//         g_pDXUTD3D9Enumeration->Enumerate( focusWindow, d3dInterface );
//    }
//
//    return g_pDXUTD3D9Enumeration.get();
//}
//
//CD3D9Enumeration::CD3D9Enumeration( )
//{
//	m_bHasEnumerated = false;
//	m_pD3D = NULL;
//	m_bRequirePostPixelShaderBlending = true;
//
//	m_nMinWidth = 640;
//	m_nMinHeight = 480;
//	m_nMaxWidth = UINT_MAX;
//	m_nMaxHeight = UINT_MAX;
//
//	m_nRefreshMin = 0;
//	m_nRefreshMax = UINT_MAX;
//
//	m_nMultisampleQualityMax = 0xFFFF;
//
//	ResetPossibleDepthStencilFormats( );
//	ResetPossibleMultisampleTypeList( );
//	ResetPossiblePresentIntervalList( );
//	SetPossibleVertexProcessingList( true, true, true, false );
//}
//
//
//CD3D9Enumeration::~CD3D9Enumeration( )
//{
//	ClearAdapterInfoList( );
//}
//
//
//static int32_t __cdecl SortModesCallback( const void* arg1, const void* arg2 )
//{
//	D3DDISPLAYMODE* pdm1 = ( D3DDISPLAYMODE* )arg1;
//	D3DDISPLAYMODE* pdm2 = ( D3DDISPLAYMODE* )arg2;
//
//	if ( pdm1->Width > pdm2->Width )
//		return 1;
//	if ( pdm1->Width < pdm2->Width )
//		return -1;
//	if ( pdm1->Height > pdm2->Height )
//		return 1;
//	if ( pdm1->Height < pdm2->Height )
//		return -1;
//	if ( pdm1->Format > pdm2->Format )
//		return 1;
//	if ( pdm1->Format < pdm2->Format )
//		return -1;
//	if ( pdm1->RefreshRate > pdm2->RefreshRate )
//		return 1;
//	if ( pdm1->RefreshRate < pdm2->RefreshRate )
//		return -1;
//	return 0;
//}
//
////--------------------------------------------------------------------------------------
//// Enumerate for each adapter all of the supported display modes, 
//// device types, adapter formats, back buffer formats, window/full screen support, 
//// depth stencil formats, multisampling types/qualities, and presentations intervals.
////
//// For each combination of device type (HAL/REF), adapter format, back buffer format, and
//// IsWindowed it will call the app's ConfirmDevice callback.  This allows the app
//// to reject or allow that combination based on its caps/etc.  It also allows the 
//// app to change the BehaviorFlags.  The BehaviorFlags defaults non-pure HWVP 
//// if supported otherwise it will default to SWVP, however the app can change this 
//// through the ConfirmDevice callback.
////--------------------------------------------------------------------------------------
//HRESULT CD3D9Enumeration::Enumerate( HWND focusWindow, const CComPtr<IDirect3D9Ex>& d3d )
//{
//	//CDXUTPerfEventGenerator eventGenerator( DXUT_PERFEVENTCOLOR, L"DXUT D3D9 Enumeration" );
//
//	m_bHasEnumerated = true;
//	m_pD3D = d3d.p;
//
//	ClearAdapterInfoList( );
//	std::vector<D3DFORMAT> adapterFormatRepo;
//
//	const D3DFORMAT allowedAdapterFormats[] =
//	{
//		D3DFMT_X8R8G8B8,
//		D3DFMT_X1R5G5B5,
//		D3DFMT_R5G6B5,
//		D3DFMT_A2R10G10B10
//	};
//
//
//	const UINT numAdapters = m_pD3D->GetAdapterCount( );
//	for ( UINT adapterOrdinal = 0;
//		  adapterOrdinal < numAdapters;
//		  adapterOrdinal++ )
//	{
//		D3d9AdapterInfo* pAdapterInfo = new D3d9AdapterInfo;
//		
//		pAdapterInfo->ordinal = adapterOrdinal;
//		m_pD3D->GetAdapterIdentifier( adapterOrdinal,		 
//									  0,
//									  &pAdapterInfo->identifier );
//
//		adapterFormatRepo.clear( );
//
//		/*
//			Get list of all display modes on this adapter.  
//			Also build a temporary list of all display adapter formats.
//		*/
//		const UINT allowedAdapterFormatsCount = ARRAYSIZE( allowedAdapterFormats );
//		
//		for ( UINT formatIndex = 0;
//			  formatIndex < allowedAdapterFormatsCount;
//			  ++formatIndex )
//		{
//			const D3DFORMAT allowedAdapterFormat = allowedAdapterFormats[formatIndex];
//			const UINT adapterModeCount =
//				m_pD3D->GetAdapterModeCount( adapterOrdinal,
//											 allowedAdapterFormat );
//			
//			for ( UINT mode = 0; mode < adapterModeCount; mode++ )
//			{
//				D3DDISPLAYMODE displayMode;
//				m_pD3D->EnumAdapterModes( adapterOrdinal,
//										  allowedAdapterFormat,
//										  mode,
//										  &displayMode );
//
//				if ( displayMode.Width < m_nMinWidth ||
//					 displayMode.Height < m_nMinHeight ||
//					 displayMode.Width > m_nMaxWidth ||
//					 displayMode.Height > m_nMaxHeight ||
//					 displayMode.RefreshRate < m_nRefreshMin ||
//					 displayMode.RefreshRate > m_nRefreshMax )
//				{
//					continue;
//				}
//
//				pAdapterInfo->displayModeList.push_back( displayMode );
//
//				auto findElem = std::find( adapterFormatRepo.begin( ),
//										   adapterFormatRepo.end( ),
//										   displayMode.Format );
//				auto notExist = adapterFormatRepo.end( );
//
//				if ( findElem == notExist )
//					adapterFormatRepo.push_back( displayMode.Format );
//			}
//
//		}
//
//		D3DDISPLAYMODE displayMode;
//		m_pD3D->GetAdapterDisplayMode( adapterOrdinal, &displayMode );
//
//		auto findElem = std::find( adapterFormatRepo.begin( ),
//								   adapterFormatRepo.end( ),
//								   displayMode.Format );
//		auto notExist = adapterFormatRepo.end( );
//
//		if ( findElem == notExist )
//			adapterFormatRepo.push_back( displayMode.Format );
//
//		// Sort displaymode list
//		qsort( &pAdapterInfo->displayModeList[0],
//			   pAdapterInfo->displayModeList.size( ), sizeof( D3DDISPLAYMODE ),
//			   SortModesCallback );
//
//		// Get info for each device on this adapter
//		if ( FAILED( EnumerateDevices( focusWindow, pAdapterInfo, &adapterFormatRepo ) ) )
//		{
//			delete pAdapterInfo;
//			continue;
//		}
//
//		// If at least one device on this adapter is available and compatible
//		// with the app, add the adapterInfo to the list
//		if ( pAdapterInfo->deviceInfoList.size( ) > 0 )
//		{
//			m_AdapterInfoList.push_back( pAdapterInfo );
//		}
//		else
//			delete pAdapterInfo;
//	}
//
//	//
//	// Check for 2 or more adapters with the same name. Append the name
//	// with some instance number if that's the case to help distinguish
//	// them.
//	//
//	bool bUniqueDesc = true;
//	D3d9AdapterInfo* pAdapterInfo;
//	for ( int32_t i = 0; i < m_AdapterInfoList.size( ); i++ )
//	{
//		D3d9AdapterInfo* pAdapterInfo1 = m_AdapterInfoList[i];
//
//		for ( int32_t j = i + 1; j < m_AdapterInfoList.size( ); j++ )
//		{
//			D3d9AdapterInfo* pAdapterInfo2 = m_AdapterInfoList[j];
//			if ( _stricmp( pAdapterInfo1->identifier.Description,
//						   pAdapterInfo2->identifier.Description ) == 0 )
//			{
//				bUniqueDesc = false;
//				break;
//			}
//		}
//
//		if ( !bUniqueDesc )
//			break;
//	}
//
//	for ( int32_t i = 0; i < m_AdapterInfoList.size( ); i++ )
//	{
//		pAdapterInfo = m_AdapterInfoList[i];
//
//		MultiByteToWideChar( CP_ACP, 0,
//							 pAdapterInfo->identifier.Description, -1,
//							 pAdapterInfo->description, 100 );
//		pAdapterInfo->description[100] = 0;
//
//		if ( !bUniqueDesc )
//		{
//			WCHAR sz[100];
//			swprintf_s( sz, 100, L" (#%d)", pAdapterInfo->ordinal );
//			wcscat_s( pAdapterInfo->description, 256, sz );
//
//		}
//	}
//
//	return S_OK;
//}
//
//
//void CD3D9Enumeration::ResetPossibleDepthStencilFormats()
//{
//    m_DepthStencilPossibleList.clear();
//    m_DepthStencilPossibleList.push_back( D3DFMT_D16 );
//    m_DepthStencilPossibleList.push_back( D3DFMT_D15S1 );
//    m_DepthStencilPossibleList.push_back( D3DFMT_D24X8 );
//    m_DepthStencilPossibleList.push_back( D3DFMT_D24S8 );
//    m_DepthStencilPossibleList.push_back( D3DFMT_D24X4S4 );
//    m_DepthStencilPossibleList.push_back( D3DFMT_D32 );
//}
//
//
////--------------------------------------------------------------------------------------
//std::vector<D3DFORMAT>* CD3D9Enumeration::GetPossibleDepthStencilFormatList()
//{
//    return &m_DepthStencilPossibleList;
//}
//
//
////--------------------------------------------------------------------------------------
//std::vector <D3DMULTISAMPLE_TYPE>* CD3D9Enumeration::GetPossibleMultisampleTypeList()
//{
//    return &m_MultiSampleTypeList;
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::ResetPossibleMultisampleTypeList()
//{
//    m_MultiSampleTypeList.clear();
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_NONE );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_NONMASKABLE );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_2_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_3_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_4_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_5_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_6_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_7_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_8_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_9_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_10_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_11_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_12_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_13_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_14_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_15_SAMPLES );
//    m_MultiSampleTypeList.push_back( D3DMULTISAMPLE_16_SAMPLES );
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::GetPossibleVertexProcessingList( bool* pbSoftwareVP, bool* pbHardwareVP, bool* pbPureHarewareVP,
//                                                        bool* pbMixedVP )
//{
//    *pbSoftwareVP = m_bSoftwareVP;
//    *pbHardwareVP = m_bHardwareVP;
//    *pbPureHarewareVP = m_bPureHarewareVP;
//    *pbMixedVP = m_bMixedVP;
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::SetPossibleVertexProcessingList( bool bSoftwareVP, bool bHardwareVP, bool bPureHarewareVP,
//                                                        bool bMixedVP )
//{
//    m_bSoftwareVP = bSoftwareVP;
//    m_bHardwareVP = bHardwareVP;
//    m_bPureHarewareVP = bPureHarewareVP;
//    m_bMixedVP = bMixedVP;
//}
//
//
////--------------------------------------------------------------------------------------
//std::vector <UINT>* CD3D9Enumeration::GetPossiblePresentIntervalList()
//{
//    return &m_PresentIntervalList;
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::ResetPossiblePresentIntervalList()
//{
//    m_PresentIntervalList.clear();
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_IMMEDIATE );
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_DEFAULT );
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_ONE );
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_TWO );
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_THREE );
//    m_PresentIntervalList.push_back( D3DPRESENT_INTERVAL_FOUR );
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::SetResolutionMinMax( UINT nMinWidth, UINT nMinHeight,
//                                            UINT nMaxWidth, UINT nMaxHeight )
//{
//    m_nMinWidth = nMinWidth;
//    m_nMinHeight = nMinHeight;
//    m_nMaxWidth = nMaxWidth;
//    m_nMaxHeight = nMaxHeight;
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::SetRefreshMinMax( UINT nMin, UINT nMax )
//{
//    m_nRefreshMin = nMin;
//    m_nRefreshMax = nMax;
//}
//
//
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::SetMultisampleQualityMax( UINT nMax )
//{
//    if( nMax > 0xFFFF )
//        nMax = 0xFFFF;
//    m_nMultisampleQualityMax = nMax;
//}
//
//CD3D9EnumDeviceSettingsCombo* CD3D9Enumeration::GetDeviceSettingsCombo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType,
//																		D3DFORMAT AdapterFormat,
//																		D3DFORMAT BackBufferFormat, BOOL bWindowed )
//{
//	CD3D9EnumDeviceInfo* pDeviceInfo = GetDeviceInfo( AdapterOrdinal, DeviceType );
//	
//	if ( pDeviceInfo )
//	{
//		for ( int32_t iDeviceCombo = 0; iDeviceCombo < pDeviceInfo->deviceSettingsComboList.size( ); iDeviceCombo++ )
//		{
//			CD3D9EnumDeviceSettingsCombo* pDeviceSettingsCombo = pDeviceInfo->deviceSettingsComboList[iDeviceCombo];
//			if ( pDeviceSettingsCombo->AdapterFormat == AdapterFormat &&
//				 pDeviceSettingsCombo->BackBufferFormat == BackBufferFormat &&
//				 pDeviceSettingsCombo->Windowed == bWindowed )
//				return pDeviceSettingsCombo;
//		}
//	}
//
//	return NULL;
//}
//
////--------------------------------------------------------------------------------------
//// Enumerates D3D devices for a particular adapter.
////--------------------------------------------------------------------------------------
//HRESULT CD3D9Enumeration::EnumerateDevices( HWND focusWindow,
//											D3d9AdapterInfo* pAdapterInfo,
//											std::vector<D3DFORMAT>* pAdapterFormatList )
//{
//	HRESULT hr;
//
//	const D3DDEVTYPE devTypeArray[] =
//	{
//		D3DDEVTYPE_HAL,
//		D3DDEVTYPE_SW,
//		D3DDEVTYPE_REF
//	};
//	const UINT devTypeArrayCount = sizeof( devTypeArray ) / sizeof( devTypeArray[0] );
//
//	// Enumerate each Direct3D device type
//	for ( UINT iDeviceType = 0; iDeviceType < devTypeArrayCount; iDeviceType++ )
//	{
//		CD3D9EnumDeviceInfo* pDeviceInfo = new CD3D9EnumDeviceInfo;
//		if ( pDeviceInfo == NULL )
//			return E_OUTOFMEMORY;
//
//		// Fill struct w/ AdapterOrdinal and D3DDEVTYPE
//		pDeviceInfo->AdapterOrdinal = pAdapterInfo->ordinal;
//		pDeviceInfo->DeviceType = devTypeArray[iDeviceType];
//
//		// Store device caps
//		if ( FAILED( hr = m_pD3D->GetDeviceCaps( pAdapterInfo->ordinal, pDeviceInfo->DeviceType,
//												 &pDeviceInfo->Caps ) ) )
//		{
//			delete pDeviceInfo;
//			continue;
//		}
//
//		if ( pDeviceInfo->DeviceType != D3DDEVTYPE_HAL )
//		{
//			// Create a temp device to verify that it is really possible to create a REF device 
//			// [the developer DirectX redist has to be installed]
//			D3DDISPLAYMODE Mode;
//			m_pD3D->GetAdapterDisplayMode( 0, &Mode );
//			D3DPRESENT_PARAMETERS pp;
//			ZeroMemory( &pp, sizeof( D3DPRESENT_PARAMETERS ) );
//			pp.BackBufferWidth = 1;
//			pp.BackBufferHeight = 1;
//			pp.BackBufferFormat = Mode.Format;
//			pp.BackBufferCount = 1;
//			pp.SwapEffect = D3DSWAPEFFECT_COPY;
//			pp.Windowed = TRUE;
//			pp.hDeviceWindow = focusWindow;
//			CComPtr<IDirect3DDevice9> pDevice = NULL;
//			if ( FAILED( hr = m_pD3D->CreateDevice( pAdapterInfo->ordinal, pDeviceInfo->DeviceType,
//													focusWindow,
//													D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE, &pp,
//													&pDevice ) ) )
//			{
//				delete pDeviceInfo;
//				continue;
//			}
//			//SAFE_RELEASE( pDevice );
//		}
//
//		// Get info for each devicecombo on this device
//		if ( FAILED( hr = EnumerateDeviceCombos( pAdapterInfo, pDeviceInfo, pAdapterFormatList ) ) )
//		{
//			delete pDeviceInfo;
//			continue;
//		}
//
//		// If at least one devicecombo for this device is found, 
//		// add the deviceInfo to the list
//		if ( pDeviceInfo->deviceSettingsComboList.size( ) > 0 )
//			pAdapterInfo->deviceInfoList.push_back( pDeviceInfo );
//		else
//			delete pDeviceInfo;
//	}
//
//	return S_OK;
//}
//
////--------------------------------------------------------------------------------------
//// Enumerates DeviceCombos for a particular device.
////--------------------------------------------------------------------------------------
//HRESULT CD3D9Enumeration::EnumerateDeviceCombos( D3d9AdapterInfo* pAdapterInfo, CD3D9EnumDeviceInfo* pDeviceInfo,
//												 std::vector <D3DFORMAT>* pAdapterFormatList )
//{
//	const D3DFORMAT backBufferFormatArray[] =
//	{
//		D3DFMT_A8R8G8B8,
//		D3DFMT_X8R8G8B8,
//		D3DFMT_A2R10G10B10,
//		D3DFMT_R5G6B5,
//		D3DFMT_A1R5G5B5,
//		D3DFMT_X1R5G5B5
//	};
//	const UINT backBufferFormatArrayCount = sizeof( backBufferFormatArray ) / sizeof( backBufferFormatArray[0] );
//
//	// See which adapter formats are supported by this device
//	for ( int32_t iFormat = 0; iFormat < pAdapterFormatList->size( ); iFormat++ )
//	{
//		D3DFORMAT adapterFormat = ( *pAdapterFormatList )[iFormat];
//
//		for ( UINT iBackBufferFormat = 0; iBackBufferFormat < backBufferFormatArrayCount; iBackBufferFormat++ )
//		{
//			D3DFORMAT backBufferFormat = backBufferFormatArray[iBackBufferFormat];
//
//			for ( int32_t nWindowed = 0; nWindowed < 2; nWindowed++ )
//			{
//				if ( !nWindowed && pAdapterInfo->displayModeList.size( ) == 0 )
//					continue;
//
//				if ( FAILED( m_pD3D->CheckDeviceType( pAdapterInfo->ordinal, pDeviceInfo->DeviceType,
//													  adapterFormat, backBufferFormat, nWindowed ) ) )
//				{
//					continue;
//				}
//
//				if ( m_bRequirePostPixelShaderBlending )
//				{
//					// If the backbuffer format doesn't support D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING
//					// then alpha test, pixel fog, render-target blending, color write enable, and dithering. 
//					// are not supported.
//					if ( FAILED( m_pD3D->CheckDeviceFormat( pAdapterInfo->ordinal, pDeviceInfo->DeviceType,
//															adapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
//															D3DRTYPE_TEXTURE, backBufferFormat ) ) )
//					{
//						continue;
//					}
//				}
//
//				// If an application callback function has been provided, make sure this device
//				// is acceptable to the app.
//				if ( !tgon::IsDeviceAcceptable( 
//							m_pD3D,
//							&pDeviceInfo->Caps,
//							adapterFormat,
//							backBufferFormat )
//						)
//					continue;
//
//				// At this point, we have an adapter/device/adapterformat/backbufferformat/iswindowed
//				// DeviceCombo that is supported by the system and acceptable to the app. We still 
//				// need to find one or more suitable depth/stencil buffer format,
//				// multisample type, and present interval.
//				CD3D9EnumDeviceSettingsCombo* pDeviceCombo = new CD3D9EnumDeviceSettingsCombo;
//				if ( pDeviceCombo == NULL )
//					return E_OUTOFMEMORY;
//
//				pDeviceCombo->AdapterOrdinal = pAdapterInfo->ordinal;
//				pDeviceCombo->DeviceType = pDeviceInfo->DeviceType;
//				pDeviceCombo->AdapterFormat = adapterFormat;
//				pDeviceCombo->BackBufferFormat = backBufferFormat;
//				pDeviceCombo->Windowed = ( nWindowed != 0 );
//
//				BuildDepthStencilFormatList( pDeviceCombo );
//				BuildMultiSampleTypeList( pDeviceCombo );
//				if ( pDeviceCombo->multiSampleTypeList.size( ) == 0 )
//				{
//					delete pDeviceCombo;
//					continue;
//				}
//				BuildDSMSConflictList( pDeviceCombo );
//				BuildPresentIntervalList( pDeviceInfo, pDeviceCombo );
//				pDeviceCombo->pAdapterInfo = pAdapterInfo;
//				pDeviceCombo->pDeviceInfo = pDeviceInfo;
//
//				pDeviceInfo->deviceSettingsComboList.push_back( pDeviceCombo );
//			}
//		}
//	}
//
//	return S_OK;
//}
//
//
//
////--------------------------------------------------------------------------------------
//// Adds all depth/stencil formats that are compatible with the device 
////       and app to the given D3DDeviceCombo.
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::BuildDepthStencilFormatList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo )
//{
//	D3DFORMAT depthStencilFmt;
//	for ( int32_t idsf = 0; idsf < m_DepthStencilPossibleList.size( ); idsf++ )
//	{
//		depthStencilFmt = m_DepthStencilPossibleList[idsf];
//		if ( SUCCEEDED( m_pD3D->CheckDeviceFormat( pDeviceCombo->AdapterOrdinal,
//												   pDeviceCombo->DeviceType, pDeviceCombo->AdapterFormat,
//												   D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, depthStencilFmt ) ) )
//		{
//			if ( SUCCEEDED( m_pD3D->CheckDepthStencilMatch( pDeviceCombo->AdapterOrdinal,
//															pDeviceCombo->DeviceType, pDeviceCombo->AdapterFormat,
//															pDeviceCombo->BackBufferFormat, depthStencilFmt ) ) )
//			{
//				pDeviceCombo->depthStencilFormatList.push_back( depthStencilFmt );
//			}
//		}
//	}
//}
//
//
//
//
////--------------------------------------------------------------------------------------
//// Adds all multisample types that are compatible with the device and app to
////       the given D3DDeviceCombo.
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::BuildMultiSampleTypeList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo )
//{
//	D3DMULTISAMPLE_TYPE msType;
//	DWORD msQuality;
//	for ( int32_t imst = 0; imst < m_MultiSampleTypeList.size( ); imst++ )
//	{
//		msType = m_MultiSampleTypeList[imst];
//		if ( SUCCEEDED( m_pD3D->CheckDeviceMultiSampleType( pDeviceCombo->AdapterOrdinal,
//															pDeviceCombo->DeviceType, pDeviceCombo->BackBufferFormat,
//															pDeviceCombo->Windowed, msType, &msQuality ) ) )
//		{
//			pDeviceCombo->multiSampleTypeList.push_back( msType );
//			if ( msQuality > m_nMultisampleQualityMax + 1 )
//				msQuality = m_nMultisampleQualityMax + 1;
//			pDeviceCombo->multiSampleQualityList.push_back( msQuality );
//		}
//	}
//}
//
//
//
//
////--------------------------------------------------------------------------------------
//// Find any conflicts between the available depth/stencil formats and
////       multisample types.
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::BuildDSMSConflictList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo )
//{
//	CD3D9EnumDSMSConflict DSMSConflict;
//
//	for ( D3DFORMAT& dsFmt : pDeviceCombo->depthStencilFormatList )
//	{
//		for ( D3DMULTISAMPLE_TYPE& msType : pDeviceCombo->multiSampleTypeList )
//		{
//			if ( FAILED( m_pD3D->CheckDeviceMultiSampleType( pDeviceCombo->AdapterOrdinal, pDeviceCombo->DeviceType,
//															 dsFmt, pDeviceCombo->Windowed, msType, NULL ) ) )
//			{
//				DSMSConflict.DSFormat = dsFmt;
//				DSMSConflict.MSType = msType;
//				pDeviceCombo->DSMSConflictList.push_back( DSMSConflict );
//			}
//		}
//	}
//}
//
//
////--------------------------------------------------------------------------------------
//// Adds all present intervals that are compatible with the device and app 
////       to the given D3DDeviceCombo.
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::BuildPresentIntervalList( CD3D9EnumDeviceInfo* pDeviceInfo,
//												 CD3D9EnumDeviceSettingsCombo* pDeviceCombo )
//{
//	UINT pi;
//	for ( int32_t ipi = 0; ipi < m_PresentIntervalList.size( ); ipi++ )
//	{
//		pi = m_PresentIntervalList[ipi];
//		if ( pDeviceCombo->Windowed )
//		{
//			if ( pi == D3DPRESENT_INTERVAL_TWO ||
//				 pi == D3DPRESENT_INTERVAL_THREE ||
//				 pi == D3DPRESENT_INTERVAL_FOUR )
//			{
//				// These intervals are not supported in windowed mode.
//				continue;
//			}
//		}
//		// Note that D3DPRESENT_INTERVAL_DEFAULT is zero, so you
//		// can't do a caps check for it -- it is always available.
//		if ( pi == D3DPRESENT_INTERVAL_DEFAULT ||
//			 ( pDeviceInfo->Caps.PresentationIntervals & pi ) )
//		{
//			pDeviceCombo->presentIntervalList.push_back( pi );
//		}
//	}
//}
//
//
//
////--------------------------------------------------------------------------------------
//// Release all the allocated D3d9AdapterInfo objects and empty the list
////--------------------------------------------------------------------------------------
//void CD3D9Enumeration::ClearAdapterInfoList( )
//{
//	D3d9AdapterInfo* pAdapterInfo;
//	for ( int32_t i = 0; i < m_AdapterInfoList.size( ); i++ )
//	{
//		pAdapterInfo = m_AdapterInfoList[i];
//		delete pAdapterInfo;
//	}
//
//	m_AdapterInfoList.clear( );
//}
//
//
//
////--------------------------------------------------------------------------------------
//// Call GetAdapterInfoList() after Enumerate() to get a STL vector of 
////       D3d9AdapterInfo* 
////--------------------------------------------------------------------------------------
//std::vector <D3d9AdapterInfo*>* CD3D9Enumeration::GetAdapterInfoList( )
//{
//	return &m_AdapterInfoList;
//}
//
//
//
////--------------------------------------------------------------------------------------
//D3d9AdapterInfo* CD3D9Enumeration::GetAdapterInfo( UINT AdapterOrdinal )
//{
//	for ( D3d9AdapterInfo* adapterInfo : m_AdapterInfoList )
//	{
//		if ( adapterInfo->ordinal == AdapterOrdinal )
//			return adapterInfo;
//	}
//
//	return NULL;
//}
//
//
////--------------------------------------------------------------------------------------
//CD3D9EnumDeviceInfo* CD3D9Enumeration::GetDeviceInfo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType )
//{
//	D3d9AdapterInfo* pAdapterInfo = GetAdapterInfo( AdapterOrdinal );
//	if ( pAdapterInfo )
//	{
//		for ( int32_t iDeviceInfo = 0; iDeviceInfo < pAdapterInfo->deviceInfoList.size( ); iDeviceInfo++ )
//		{
//			CD3D9EnumDeviceInfo* pDeviceInfo = pAdapterInfo->deviceInfoList[iDeviceInfo];
//			if ( pDeviceInfo->DeviceType == DeviceType )
//				return pDeviceInfo;
//		}
//	}
//
//	return NULL;
//}