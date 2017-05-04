/*
* @author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <OISKeyboard.h>


namespace tgon
{


enum class KeyCode
{
	Unassigned		= OIS::KeyCode::KC_UNASSIGNED,
	Escape			= OIS::KeyCode::KC_ESCAPE,
	Keypad1			= OIS::KeyCode::KC_1,
	Keypad2			= OIS::KeyCode::KC_2,
	Keypad3			= OIS::KeyCode::KC_3,
	Keypad4			= OIS::KeyCode::KC_4,
	Keypad5			= OIS::KeyCode::KC_5,
	Keypad6			= OIS::KeyCode::KC_6,
	Keypad7			= OIS::KeyCode::KC_7,
	Keypad8			= OIS::KeyCode::KC_8,
	Keypad9			= OIS::KeyCode::KC_9,
	Keypad0			= OIS::KeyCode::KC_0,
	KeypadMinus		= OIS::KeyCode::KC_MINUS,
	KeypadEquals	= OIS::KeyCode::KC_EQUALS,
	Backspace		= OIS::KeyCode::KC_BACK,
	Tab				= OIS::KeyCode::KC_TAB,
	Q				= OIS::KeyCode::KC_Q,
	W				= OIS::KeyCode::KC_W,
	E				= OIS::KeyCode::KC_E,
	R				= OIS::KeyCode::KC_R,
	T				= OIS::KeyCode::KC_T,
	Y				= OIS::KeyCode::KC_Y,
	U				= OIS::KeyCode::KC_U,
	I				= OIS::KeyCode::KC_I,
	O				= OIS::KeyCode::KC_O,
	P				= OIS::KeyCode::KC_P,
	LeftBracket		= OIS::KeyCode::KC_LBRACKET,
	RightBracket	= OIS::KeyCode::KC_RBRACKET,
	Return			= OIS::KeyCode::KC_RETURN,    // Enter
	LeftCtrl		= OIS::KeyCode::KC_LCONTROL,
	A				= OIS::KeyCode::KC_A,
	S				= OIS::KeyCode::KC_S,
	D				= OIS::KeyCode::KC_D,
	F				= OIS::KeyCode::KC_F,
	G				= OIS::KeyCode::KC_G,
	H				= OIS::KeyCode::KC_H,
	J				= OIS::KeyCode::KC_J,
	K				= OIS::KeyCode::KC_K,
	L				= OIS::KeyCode::KC_L,
	Semicolon		= OIS::KeyCode::KC_SEMICOLON,	// ;
	//OIS::KeyCode::KC_APOSTROPHE,
	//OIS::KeyCode::KC_GRAVE,    // accent
	LeftShift		= OIS::KeyCode::KC_LSHIFT,
	Backslash		= OIS::KeyCode::KC_BACKSLASH,
	Z				= OIS::KeyCode::KC_Z,
	X				= OIS::KeyCode::KC_X,
	C				= OIS::KeyCode::KC_C,
	V				= OIS::KeyCode::KC_V,
	B				= OIS::KeyCode::KC_B,
	N				= OIS::KeyCode::KC_N,
	M				= OIS::KeyCode::KC_M,
	Comma			= OIS::KeyCode::KC_COMMA,		// ,
	Period			= OIS::KeyCode::KC_PERIOD,		// .
	Slash			= OIS::KeyCode::KC_SLASH,		// /
	RightShift		= OIS::KeyCode::KC_RSHIFT,
	Multiply		= OIS::KeyCode::KC_MULTIPLY,	// *
	LeftAlt			= OIS::KeyCode::KC_LMENU,
	Space			= OIS::KeyCode::KC_SPACE,
	//OIS::KeyCode::KC_CAPITAL,
	F1				= OIS::KeyCode::KC_F1,
	F2				= OIS::KeyCode::KC_F2,
	F3				= OIS::KeyCode::KC_F3,
	F4				= OIS::KeyCode::KC_F4,
	F5				= OIS::KeyCode::KC_F5,
	F6				= OIS::KeyCode::KC_F6,
	F7				= OIS::KeyCode::KC_F7,
	F8				= OIS::KeyCode::KC_F8,
	F9				= OIS::KeyCode::KC_F9,
	F10				= OIS::KeyCode::KC_F10,
	F11				= OIS::KeyCode::KC_F11,
	F12				= OIS::KeyCode::KC_F12,
	F13				= OIS::KeyCode::KC_F13,
	F14				= OIS::KeyCode::KC_F14,
	F15				= OIS::KeyCode::KC_F15,
	NumLock = OIS::KeyCode::KC_NUMLOCK,
	ScrollLock = OIS::KeyCode::KC_SCROLL,     // Scroll Lock
	//OIS::KeyCode::KC_NUMPAD7,
	//OIS::KeyCode::KC_NUMPAD8,
	//OIS::KeyCode::KC_NUMPAD9,
	Subtract = OIS::KeyCode::KC_SUBTRACT,    // - on numeric keypad
	//OIS::KeyCode::KC_NUMPAD4,
	//OIS::KeyCode::KC_NUMPAD5,
	//OIS::KeyCode::KC_NUMPAD6,
	Add = OIS::KeyCode::KC_ADD,    // + on numeric keypad
	//OIS::KeyCode::KC_NUMPAD1,
	//OIS::KeyCode::KC_NUMPAD2,
	//OIS::KeyCode::KC_NUMPAD3,
	//OIS::KeyCode::KC_NUMPAD0,
	Decimal = OIS::KeyCode::KC_DECIMAL,    // . on numeric keypad
	//OIS::KeyCode::KC_OEM_102,    // < > | on UK/Germany keyboards
	//OIS::KeyCode::KC_KANA,    // (Japanese keyboard)
	//OIS::KeyCode::KC_ABNT_C1,    // / ? on Portugese (Brazilian) keyboards
	//OIS::KeyCode::KC_CONVERT,    // (Japanese keyboard)
	//OIS::KeyCode::KC_NOCONVERT,    // (Japanese keyboard)
	//OIS::KeyCode::KC_YEN,    // (Japanese keyboard)
	//OIS::KeyCode::KC_ABNT_C2,    // Numpad . on Portugese (Brazilian) keyboards
	//OIS::KeyCode::KC_NUMPADEQUALS,    // = on numeric keypad (NEC PC98)
	//OIS::KeyCode::KC_PREVTRACK,    // Previous Track (KC_CIRCUMFLEX on Japanese keyboard)
	//OIS::KeyCode::KC_AT = 0x91,    //                     (NEC PC98)
	//OIS::KeyCode::KC_COLON = 0x92,    //                     (NEC PC98)
	//OIS::KeyCode::KC_UNDERLINE,    //                     (NEC PC98)
	//OIS::KeyCode::KC_KANJI,    // (Japanese keyboard)
	//OIS::KeyCode::KC_STOP,    //                     (NEC PC98)
	//OIS::KeyCode::KC_AX,    //                     (Japan AX)
	//OIS::KeyCode::KC_UNLABELED,    //                        (J3100)
	//OIS::KeyCode::KC_NEXTTRACK,    // Next Track
	//OIS::KeyCode::KC_NUMPADENTER,    // Enter on numeric keypad
	//OIS::KeyCode::KC_RCONTROL,
	//OIS::KeyCode::KC_MUTE,    // Mute
	//OIS::KeyCode::KC_CALCULATOR,    // Calculator
	//OIS::KeyCode::KC_PLAYPAUSE,    // Play / Pause
	//OIS::KeyCode::KC_MEDIASTOP,    // Media Stop
	//OIS::KeyCode::KC_VOLUMEDOWN,    // Volume -
	//OIS::KeyCode::KC_VOLUMEUP,    // Volume +
	//OIS::KeyCode::KC_WEBHOME,    // Web home
	//OIS::KeyCode::KC_NUMPADCOMMA,    // , on numeric keypad (NEC PC98)
	Device = OIS::KeyCode::KC_DIVIDE,    // / on numeric keypad
	//OIS::KeyCode::KC_SYSRQ,
	//OIS::KeyCode::KC_RMENU,    // right Alt
	//OIS::KeyCode::KC_PAUSE,    // Pause
	Home = OIS::KeyCode::KC_HOME,    // Home on arrow keypad
	End = OIS::KeyCode::KC_END,    // End on arrow keypad
	LeftArrow = OIS::KeyCode::KC_LEFT,    // LeftArrow on arrow keypad
	RightArrow = OIS::KeyCode::KC_RIGHT,    // RightArrow on arrow keypad
	UpArrow = OIS::KeyCode::KC_UP,    // UpArrow on arrow keypad
	DownArrow = OIS::KeyCode::KC_DOWN,    // DownArrow on arrow keypad
	PageUp = OIS::KeyCode::KC_PGUP,    // PgUp on arrow keypad
	PageDown = OIS::KeyCode::KC_PGDOWN,    // PgDn on arrow keypad
	Insert = OIS::KeyCode::KC_INSERT,    // Insert on arrow keypad
	Delete = OIS::KeyCode::KC_DELETE,    // Delete on arrow keypad
	LeftWindows = OIS::KeyCode::KC_LWIN,    // Left Windows key
	RightWindows = OIS::KeyCode::KC_RWIN,    // Right Windows key
	//OIS::KeyCode::KC_APPS,    // AppMenu key
	Power = OIS::KeyCode::KC_POWER,    // System Power
	Sleep = OIS::KeyCode::KC_SLEEP,    // System Sleep
	Wake = OIS::KeyCode::KC_WAKE,    // System Wake
	//OIS::KeyCode::KC_WEBSEARCH,    // Web Search
	//OIS::KeyCode::KC_WEBFAVORITES,    // Web Favorites
	//OIS::KeyCode::KC_WEBREFRESH,    // Web Refresh
	//OIS::KeyCode::KC_WEBSTOP,    // Web Stop
	//OIS::KeyCode::KC_WEBFORWARD,    // Web Forward
	//OIS::KeyCode::KC_WEBBACK,    // Web Back
	//OIS::KeyCode::KC_MYCOMPUTER,    // My Computer
	//OIS::KeyCode::KC_MAIL,    // Mail
	//OIS::KeyCode::KC_MEDIASELECT     // Media Select
};


}