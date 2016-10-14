/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Generic/GenericWindowFrame.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>


namespace tgon
{


enum RawInputType : USHORT
{
	kPointer = 0x01,
	kMouse = 0x02,
	kJoyStick = 0x04,
	kGamePad = 0x05,
	kKeyboard = 0x06,
	kKeyPad = 0x07,
};

class TGON_API WindowsWindowFrame : 
	public GenericWindowFrame<WindowsWindowFrame>,
	public IDropTarget
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	explicit WindowsWindowFrame( _In_ const WindowStyle& wndStyle );
	virtual ~WindowsWindowFrame( );

	/* 
	 * Commands
	*/ 
public:
	bool PumpEvent( );
	void Show( );
	void Hide( );
	void Quit( );
	void Maximize( );
	void Minimize( );
	void BringToFront( );
	void Flash( );
	
	/*
	 * Event handlers
	*/
	virtual LRESULT OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	/*
	 * COM Interfaces
	*/
	STDMETHODIMP QueryInterface( REFIID riid, void** ppvObject ) override;
	STDMETHODIMP_( ULONG ) AddRef( ) override;
	STDMETHODIMP_( ULONG ) Release( ) override;
	STDMETHODIMP DragEnter( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragOver( DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragLeave( ) override;
	STDMETHODIMP Drop( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;

	/* 
	 * Sets
	*/ 
public:
	void SetPosition( int32_t x, int32_t y );
	void SetScale( int32_t width, int32_t height );
	void SetCaption( /*In*/ const wchar_t* caption );
	
	/* 
		@note				Enable global input hook
		@param	isEnable	Enable or Disable
		@param	inputFlag	OR input flag
		@return				If failed, then GetLastError code, 0 otherwise.
	*/
	DWORD EnableGlobalInputHook( bool isEnable, RawInputType inputFlag );

	/* 
	 * Gets
	*/ 
	void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const;
	void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const;
	void GetCaptionText( /*Out*/ wchar_t* caption ) const;
	HWND GetWindowHandle( ) const;
	bool IsEnabledGlobalInputHook( ) const;

	/* 
	 * Internal works
	*/ 
private:
	void AdditionalInit( /*In*/ const WindowStyle& );

	/* 
	 * Variables
	*/ 
private:
	uint32_t m_comRefCount;
	const HWND m_wndHandle;
	bool m_enabledGlobalInputHook;
};


using WindowFrame = WindowsWindowFrame;


} /*namespace tgon*/