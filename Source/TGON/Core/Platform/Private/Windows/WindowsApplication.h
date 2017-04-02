/**
 * filename WindowsApplication.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "../Generic/GenericApplication.h"

#include <cstdint>

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

#ifdef RegisterClass
#   undef RegisterClass
#endif

namespace tgon
{

class TGON_API WindowsApplication :
	public GenericApplication<WindowsApplication>
{
/** 
 * @section Ctor/Dtor
 */
public:
	WindowsApplication() = delete;
	~WindowsApplication() = delete;

/**
 * @section Commands
 */
public:
	/**
	 * @brief               Pull out the message from all queue.
     * @param   message     Message to pull out
	 * @return              False if there is no message to pull out
	 */
    static bool PullMessage(_Out_ MSG* message);
    /**
	 * @brief               Pull out the message from specified window's message queue.
     * @param   window      The window to pull out message from its queue
     * @param   message     Message to pull out
	 * @return              False if there is no message to pull out
	 */
    static bool PullMessage(_In_ const class WindowsWindowFrame* window, _Out_ MSG* message);
    /**
	 * @brief               Pull out the message from all queue and dispatch it.
     * @param   message     Message to pull out
	 * @return              False if there is no message to pull out
	 */
	static bool PumpMessage(_Out_ MSG* message);

    static void ShowMessageBox(const char* message, const char* caption = "");
    static void ShowMessageBox(const wchar_t* message, const wchar_t* caption = L"");
	
	/**
	 * @brief               Post quit message to message queue.
	 * @param   exitCode    Exit code
	 */
	static void Quit(int32_t exitCode);

	/**
	 * @brief               Terminate thread by force.
	 * @param	exitCode	Exit code
	 */
	static void ExitThread(int32_t exitCode);

	/**
	 * @brief               Enable show cursor mode: Hide or Show
	 * @param   enableShow	Pass true to show, false otherwise.
	 */
	static void ShowCursor(bool enableShow);

	/**
	 * @brief   Enable float calculate exception like: devide by zero, underflow, overflow, etc 
	 */
	static void EnableFloatingException(unsigned int newStat);

	/**/
	//static void DisableTaskSwitching();

	/**
	 * Event handlers
	 */
public:
	static LRESULT CALLBACK OnMessageHandled(_In_ HWND wndHandle, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam);

	/**
	 * Variables
	 */
public:
	static const HINSTANCE InstanceHandle;
	static const wchar_t* AppClassName;
};

using TApplication = WindowsApplication;

} /* namespace tgon */
