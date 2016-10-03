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


class TGON_API WindowsWindowFrame : 
	public GenericWindowFrame,
	public IDropTarget
{
	// 
	// Ctor/Dtor
	// 
public:
	explicit WindowsWindowFrame( _In_ const WindowStyle& wndStyle );
	virtual ~WindowsWindowFrame( );

public:
	// 
	// Commands
	// 
	virtual bool PumpEvent( ) override;
	virtual void Show( ) override;
	virtual void Hide( ) override;
	virtual void Quit( ) override;
	virtual void Maximize( ) override;
	virtual void Minimize( ) override;
	virtual void BringToFront( ) override;
	virtual void Flash( ) override;
	
	//
	// Event handlers
	//
	virtual LRESULT OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	//
	// COM Interfaces
	//
	STDMETHODIMP QueryInterface( REFIID riid, void** ppvObject ) override;
	STDMETHODIMP_( ULONG ) AddRef( ) override;
	STDMETHODIMP_( ULONG ) Release( ) override;
	STDMETHODIMP DragEnter( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragOver( DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;
	STDMETHODIMP DragLeave( ) override;
	STDMETHODIMP Drop( LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect ) override;

	// 
	// Sets
	// 
	virtual void SetPosition( int32_t x, int32_t y ) override;
	virtual void SetScale( int32_t width, int32_t height ) override;
	virtual void SetCaption( /*In*/ const wchar_t* caption ) override;
	void EnableGlobalMouseFocus( bool isEnable );

	// 
	// Gets
	// 
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const override;
	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const override;
	virtual void GetCaptionText( /*Out*/ wchar_t* caption ) const override;
	HWND GetWindowHandle( ) const;
	bool IsEnabledGlobalInputFocus( ) const;


	// 
	// Internal works
	// 
private:
	void AdditionalInit( /*In*/ const WindowStyle& );

	// 
	// Private variables
	// 
private:
	/* @note com reference count */
	uint32_t m_refCount;

	/* @note com reference count */
	const HWND m_wndHandle;

	/* @note com reference count */
	bool m_enabledGlobalMouseFocus;
};

using TWindowFrame = WindowsWindowFrame;


} /*namespace tgon*/