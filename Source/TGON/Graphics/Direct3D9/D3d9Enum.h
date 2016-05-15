#pragma once
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <atlbase.h>
//#include <vector>
//#include "D3d9Type.h"
//
//
//class CD3D9Enumeration;
//struct D3D9DeviceSettings;
//struct DXUTMatchOptions;
//struct CD3D9EnumDeviceSettingsCombo;
//class D3d9AdapterInfo;
//class CD3D9EnumDeviceInfo;
//struct CD3D9EnumDSMSConflict;
//
//
//enum DXUT_MATCH_TYPE
//{
//	DXUTMT_IGNORE_INPUT = 0,  // Use the closest valid value to a default 
//	DXUTMT_PRESERVE_INPUT,    // Use input without change, but may cause no valid device to be found
//	DXUTMT_CLOSEST_TO_INPUT   // Use the closest valid value to the input 
//};
//
//struct D3D9DeviceSettings
//{
//	UINT AdapterOrdinal;
//	D3DDEVTYPE DeviceType;
//	D3DFORMAT AdapterFormat;
//	DWORD BehaviorFlags;
//	D3DPRESENT_PARAMETERS pp;
//};
//
//struct DXUTMatchOptions
//{
//	DXUT_MATCH_TYPE eAdapterOrdinal;
//	DXUT_MATCH_TYPE eOutput;
//	DXUT_MATCH_TYPE eDeviceType;
//	DXUT_MATCH_TYPE eWindowed;
//	DXUT_MATCH_TYPE eAdapterFormat;
//	DXUT_MATCH_TYPE eVertexProcessing;
//	DXUT_MATCH_TYPE eResolution;
//	DXUT_MATCH_TYPE eBackBufferFormat;
//	DXUT_MATCH_TYPE eBackBufferCount;
//	DXUT_MATCH_TYPE eMultiSample;
//	DXUT_MATCH_TYPE eSwapEffect;
//	DXUT_MATCH_TYPE eDepthFormat;
//	DXUT_MATCH_TYPE eStencilFormat;
//	DXUT_MATCH_TYPE ePresentFlags;
//	DXUT_MATCH_TYPE eRefreshRate;
//	DXUT_MATCH_TYPE ePresentInterval;
//};
//
//CD3D9Enumeration* DXUTGetD3D9Enumeration( HWND focusWindow,
//										  IDirect3D9Ex* d3dInterface,
//										  bool bForceEnumerate = false );
//
//struct CD3D9EnumDeviceSettingsCombo
//{
//	UINT AdapterOrdinal;
//	D3DDEVTYPE DeviceType;
//	D3DFORMAT AdapterFormat;
//	D3DFORMAT BackBufferFormat;
//	BOOL Windowed;
//
//
//	// TODO: change to reference counting version
//	std::vector<D3DFORMAT> depthStencilFormatList; // List of D3DFORMATs
//	std::vector<D3DMULTISAMPLE_TYPE> multiSampleTypeList; // List of D3DMULTISAMPLE_TYPEs
//	std::vector<DWORD> multiSampleQualityList; // List of number of quality levels for each multisample type
//	std::vector<UINT> presentIntervalList; // List of D3DPRESENT flags
//	std::vector<CD3D9EnumDSMSConflict> DSMSConflictList; // List of CD3D9EnumDSMSConflict
//
//	D3d9AdapterInfo* pAdapterInfo;
//	CD3D9EnumDeviceInfo* pDeviceInfo;
//};
//
//class CD3D9Enumeration
//{
//public:
//    // These should be called before Enumerate(). 
//    //
//    // Use these calls and the IsDeviceAcceptable to control the contents of 
//    // the enumeration object, which affects the device selection and the device settings dialog.
//    void	SetRequirePostPixelShaderBlending( bool bRequire )
//    {
//        m_bRequirePostPixelShaderBlending = bRequire;
//    }
//    void	SetResolutionMinMax( UINT nMinWidth, UINT nMinHeight, UINT nMaxWidth, UINT nMaxHeight );
//    void	SetRefreshMinMax( UINT nMin, UINT nMax );
//    void	SetMultisampleQualityMax( UINT nMax );
//    void	GetPossibleVertexProcessingList( bool* pbSoftwareVP, bool* pbHardwareVP,
//                                                             bool* pbPureHarewareVP, bool* pbMixedVP );
//    void	SetPossibleVertexProcessingList( bool bSoftwareVP, bool bHardwareVP, bool bPureHarewareVP,
//                                                             bool bMixedVP );
//    std::vector <D3DFORMAT>* GetPossibleDepthStencilFormatList();
//	std::vector <D3DMULTISAMPLE_TYPE>* GetPossibleMultisampleTypeList();
//	std::vector <UINT>* GetPossiblePresentIntervalList();
//    void	ResetPossibleDepthStencilFormats();
//    void	ResetPossibleMultisampleTypeList();
//    void	ResetPossiblePresentIntervalList();
//
//    // Call Enumerate() to enumerate available D3D adapters, devices, modes, etc.
//    bool	HasEnumerated()
//    {
//        return m_bHasEnumerated;
//    }
//    HRESULT	Enumerate( HWND focusWindow, const CComPtr<IDirect3D9Ex>& d3d );
//
//    // These should be called after Enumerate() is called
//	std::vector <D3d9AdapterInfo*>* GetAdapterInfoList();
//	D3d9AdapterInfo* GetAdapterInfo( UINT AdapterOrdinal );
//    CD3D9EnumDeviceInfo* GetDeviceInfo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType );
//	CD3D9EnumDeviceSettingsCombo* GetDeviceSettingsCombo( D3D9DeviceSettings* pD3D9DeviceSettings )
//    {
//        return GetDeviceSettingsCombo( pD3D9DeviceSettings->AdapterOrdinal, pD3D9DeviceSettings->DeviceType,
//                                       pD3D9DeviceSettings->AdapterFormat, pD3D9DeviceSettings->pp.BackBufferFormat,
//                                       pD3D9DeviceSettings->pp.Windowed );
//    }
//    CD3D9EnumDeviceSettingsCombo* GetDeviceSettingsCombo( UINT AdapterOrdinal, D3DDEVTYPE DeviceType,
//                                                          D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
//                                                          BOOL Windowed );
//
//    ~CD3D9Enumeration();
//
//private:
//    friend HRESULT WINAPI   DXUTCreateD3D9Enumeration();
//
//    // Use DXUTGetD3D9Enumeration() to access global instance
//                            CD3D9Enumeration();
//
//    bool m_bHasEnumerated;
//	CComPtr<IDirect3D9Ex> m_pD3D;
//    bool m_bRequirePostPixelShaderBlending;
//	std::vector<D3DFORMAT> m_DepthStencilPossibleList;
//	std::vector<D3DMULTISAMPLE_TYPE> m_MultiSampleTypeList;
//	std::vector<UINT> m_PresentIntervalList;
//
//    bool m_bSoftwareVP;
//    bool m_bHardwareVP;
//    bool m_bPureHarewareVP;
//    bool m_bMixedVP;
//
//    UINT m_nMinWidth;
//    UINT m_nMaxWidth;
//    UINT m_nMinHeight;
//    UINT m_nMaxHeight;
//    UINT m_nRefreshMin;
//    UINT m_nRefreshMax;
//    UINT m_nMultisampleQualityMax;
//
//    // Array of D3d9AdapterInfo* with unique AdapterOrdinals
//    std::vector <D3d9AdapterInfo*> m_AdapterInfoList;
//
//    HRESULT     EnumerateDevices( HWND focusWindow,
//								  D3d9AdapterInfo* pAdapterInfo,
//								  std::vector<D3DFORMAT>* pAdapterFormatList );
//    HRESULT     EnumerateDeviceCombos( D3d9AdapterInfo* pAdapterInfo,
//                                    CD3D9EnumDeviceInfo* pDeviceInfo,
//									   std::vector<D3DFORMAT>* pAdapterFormatList );
//    void    BuildDepthStencilFormatList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
//    void    BuildMultiSampleTypeList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
//    void    BuildDSMSConflictList( CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
//    void    BuildPresentIntervalList( CD3D9EnumDeviceInfo* pDeviceInfo,
//                                 CD3D9EnumDeviceSettingsCombo* pDeviceCombo );
//    void    ClearAdapterInfoList();
//};
//
//
////--------------------------------------------------------------------------------------
//// A class describing a Direct3D device that contains a 
////       unique supported device type 
////--------------------------------------------------------------------------------------
//class CD3D9EnumDeviceInfo
//{
//public:
//	~CD3D9EnumDeviceInfo( )
//	{
//		for ( CD3D9EnumDeviceSettingsCombo* elem : deviceSettingsComboList ) {
//			delete elem;
//		}
//	}
//
//	UINT AdapterOrdinal;
//	D3DDEVTYPE DeviceType;
//	D3DCAPS9 Caps;
//
//	// List of CD3D9EnumDeviceSettingsCombo* with a unique set 
//	// of AdapterFormat, BackBufferFormat, and Windowed
//	std::vector<CD3D9EnumDeviceSettingsCombo*> deviceSettingsComboList;
//};
//
//
////--------------------------------------------------------------------------------------
//// A class describing an adapter which contains a unique adapter ordinal 
//// that is installed on the system
////--------------------------------------------------------------------------------------
//class D3d9AdapterInfo
//{
//public:
//	~D3d9AdapterInfo( )
//	{
//		for ( CD3D9EnumDeviceInfo* elem : deviceInfoList ) {
//			delete elem;
//		}
//	}
//
//	UINT ordinal;
//	D3DADAPTER_IDENTIFIER9 identifier;
//	WCHAR description[256];
//
//	std::vector<D3DDISPLAYMODE> displayModeList; // Array of supported D3DDISPLAYMODEs
//	std::vector<CD3D9EnumDeviceInfo*> deviceInfoList; // Array of CD3D9EnumDeviceInfo* with unique supported DeviceTypes
//};
//
//
//
////--------------------------------------------------------------------------------------
//// A depth/stencil buffer format that is incompatible with a
//// multisample type.
////--------------------------------------------------------------------------------------
//struct CD3D9EnumDSMSConflict
//{
//	D3DFORMAT DSFormat;
//	D3DMULTISAMPLE_TYPE MSType;
//};