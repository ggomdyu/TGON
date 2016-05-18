/*
* Author : Junho-Cha
* Date : 05/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


enum struct WindowsMsgBoxResult
{
	Ok		= IDOK,
	Cancel	= IDCANCEL,
	Abort	= IDABORT,
	Retry	= IDRETRY,
	Ignore	= IDIGNORE,
	Yes		= IDYES,
	No		= IDNO,
};


enum struct WindowsMsgBoxButton
{
	Ok					= MB_OK,
	OkCancel			= MB_OKCANCEL,
	AbortRetryIgnore	= MB_ABORTRETRYIGNORE,
	YesNoCancel			= MB_YESNOCANCEL,
	YesNo				= MB_YESNO,
	RetryCancel			= MB_RETRYCANCEL,
#if ( WINVER >= 0x0500 )
	CencelTryContinue	= MB_CANCELTRYCONTINUE,
#endif /* WINVER >= >= 0x0500 */
};


enum struct WindowsMsgBoxFlag
{
	None				= 0,
	IconHand			= MB_ICONHAND,
	IconQuestion		= MB_ICONQUESTION,
	IconExclamation		= MB_ICONEXCLAMATION,
	IconAsterisk		= MB_ICONASTERISK,
#if ( WINVER >= 0x0400 )
	UserIcon			= MB_USERICON,
	IconWarning			= MB_ICONWARNING,
	IconError			= MB_ICONERROR,
#endif /* WINVER >= 0x0400 */
	IconInformation		= MB_ICONINFORMATION,
	IconStop			= MB_ICONSTOP,
	DefButton1			= MB_DEFBUTTON1,
	DefButton2			= MB_DEFBUTTON2,
	DefButton3			= MB_DEFBUTTON3,
#if ( WINVER >= 0x0400 )
	DefButton4			= MB_DEFBUTTON4,
#endif /* WINVER >= 0x0400 */
	AppModal			= MB_APPLMODAL,
	SystemModal			= MB_SYSTEMMODAL,
	TaskModal			= MB_TASKMODAL,
#if ( WINVER >= 0x0400 )
	Help				= MB_HELP,
#endif /* WINVER >= 0x0400 */
	NoFocus				= MB_NOFOCUS,
	SetForeground		= MB_SETFOREGROUND,
	DefaultDesktopOnly	= MB_DEFAULT_DESKTOP_ONLY,
#if ( WINVER >= 0x0400 )
	TopMost				= MB_TOPMOST,
	Right				= MB_RIGHT,
	RTLReading			= MB_RTLREADING,
#endif /* WINVER >= 0x0400 */
#ifdef _WIN32_WINNT
	ServiceNotification = MB_SERVICE_NOTIFICATION,
	ServiceNotificationNT3X = MB_SERVICE_NOTIFICATION_NT3X,
#endif /* _WIN32_WINNT */
	TypeMask			= MB_TYPEMASK,
	IconMask			= MB_ICONMASK,
	DefMask				= MB_DEFMASK,
	ModeMask			= MB_MODEMASK,
	MiscMask			= MB_MISCMASK,
};


}