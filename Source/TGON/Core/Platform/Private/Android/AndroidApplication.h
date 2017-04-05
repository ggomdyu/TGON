/**
 * filename AndroidApplication.h
 * author   ggomdyu
 * since    04/05/2017
 */

#pragma once
#include "../Generic/GenericApplication.h"

//#include "AndroidApplicationFwd.h"
#include <cstdint>

namespace tgon
{

class TGON_API WindowsApplication
{
/** 
 * @section Ctor/Dtor
 */
public:
	WindowsApplication() = delete;
	~WindowsApplication() = delete;

/**
 * @section Public command methods
 */
public:
	/**
	 * @brief                   Pull out the message from all queue.
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
    static bool PullMessage(MSG* message);
    /**
	 * @brief                   Pull out the message from specified window's message queue.
     * @param [in]  window      The window to pull out message from its queue
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
    static bool PullMessage(const class WindowsWindowFrame* window, MSG* message);
    /**
	 * @brief                   Pull out the message from all queue and dispatch it.
     * @param [out] message     Message to pull out
	 * @return                  False if there is no message to pull out
	 */
	static bool PumpMessage(MSG* message);

	static bool EnableScreenpdate(bool enable);

    /**
	 * @brief                   Show the Message box which has buttons: Yes, No
     * @param [out] message     Message box description
     * @param [out] caption     Message box title
     * @param [out] handler     Message box event handler when called button clicked
	 * @return                  False if there is no message to pull out
	 */ 
    static void ShowYesNoPopup(const char* message, const char* caption, OnPopupEventHandle handler);
    static void ShowYesNoPopup(const wchar_t* message, const wchar_t* caption, OnPopupEventHandle handler);
    static void ShowOkPopup(const char* message, const char* caption, OnPopupEventHandle handler);
    static void ShowOkPopup(const wchar_t* message, const wchar_t* caption, OnPopupEventHandle handler);
	
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
 * @section Public variables
 */
};

using TApplication = GenericApplication<AndroidApplication>;

} /* namespace tgon */
