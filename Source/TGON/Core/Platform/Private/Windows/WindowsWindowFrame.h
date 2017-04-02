/**
 * filename WindowsWindowFrame.h
 * author   ggomdyu
 * since    11/12/2015
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
/** 
 * @section Ctor/Dtor
 */ 
public:
	explicit WindowsWindowFrame(_In_ const WindowStyle& wndStyle);
	virtual ~WindowsWindowFrame();

/** 
 * @section Public methods
 */ 
public:
    bool PumpEvent();
    void Show();
    void Hide();
    void Quit();
    void Maximize();
    void Minimize();
    void BringToFront();
    void Flash();

/**
 * @section Event handlers
 */
    virtual LRESULT OnMessageHandled(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @section COM Interfaces
 */
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject) override;
    STDMETHODIMP_(ULONG) AddRef() override;
    STDMETHODIMP_(ULONG) Release() override;
    STDMETHODIMP DragEnter(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;
    STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;
    STDMETHODIMP DragLeave() override;
    STDMETHODIMP Drop(LPDATAOBJECT pDataObj, DWORD grfKeyState, POINTL pt, LPDWORD pdwEffect) override;

/**
 * @section Sets
 */
public:
    void SetPosition(int32_t x, int32_t y);
    void SetScale(int32_t width, int32_t height);
    void SetCaption(_In_ const wchar_t* caption);

	/**
	 * @brief               Enable global input hook
	 * @param   isEnable    Enable or Disable
	 * @param   inputFlag   OR input flag
	 * @return              If failed, then GetLastError code, 0 otherwise.
	 */
    DWORD EnableGlobalInputHook(bool isEnable, RawInputType inputFlag);

/** 
 * @section Gets
 */ 
    void GetPosition(/*Out*/ int32_t* x, /*Out*/ int32_t* y) const;
    void GetSize(/*Out*/ int32_t* width, /*Out*/ int32_t* height) const;
    void GetCaptionText(/*Out*/ wchar_t* caption) const;
    HWND GetWindowHandle() const;
    bool IsEnabledGlobalInputHook() const;

/** 
 * @section Private methods
 */ 
private:
	void AdditionalInit( /*In*/ const WindowStyle& );

/** 
 * @section Private variables
 */ 
private:
	uint32_t m_comRefCount;
	const HWND m_wndHandle;
	bool m_enabledGlobalInputHook;
};

using TWindowFrame = WindowsWindowFrame;

} /* namespace tgon */
