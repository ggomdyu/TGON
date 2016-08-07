/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "Interface/IModule.h"

#include <OISInputManager.h>
#include <OISException.h>		// Not used
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISEvents.h>

#include <cstdint>
#include <Console/TConsole.h>


namespace tgon
{


enum class KeyCode
{
	Unassigned = OIS::KeyCode::KC_UNASSIGNED,
	Escape = OIS::KeyCode::KC_ESCAPE,
	Keypad1 = OIS::KeyCode::KC_1,
	Keypad2 = OIS::KeyCode::KC_2,
	Keypad3 = OIS::KeyCode::KC_3,
	Keypad4 = OIS::KeyCode::KC_4,
	Keypad5 = OIS::KeyCode::KC_5,
	Keypad6 = OIS::KeyCode::KC_6,
	Keypad7 = OIS::KeyCode::KC_7,
	Keypad8 = OIS::KeyCode::KC_8,
	Keypad9 = OIS::KeyCode::KC_9,
	Keypad0 = OIS::KeyCode::KC_0,
	KeypadMinus = OIS::KeyCode::KC_MINUS,
	KeypadEquals = OIS::KeyCode::KC_EQUALS,
	Backspace = OIS::KeyCode::KC_BACK,
	Tab = OIS::KeyCode::KC_TAB,
	Q = OIS::KeyCode::KC_Q,
	W = OIS::KeyCode::KC_W,
	E = OIS::KeyCode::KC_E,
	R = OIS::KeyCode::KC_R,
	T = OIS::KeyCode::KC_T,
	Y = OIS::KeyCode::KC_Y,
	U = OIS::KeyCode::KC_U,
	I = OIS::KeyCode::KC_I,
	O = OIS::KeyCode::KC_O,
	P = OIS::KeyCode::KC_P,
	//OIS::KeyCode::KC_LBRACKET,
	//OIS::KeyCode::KC_RBRACKET,
	//OIS::KeyCode::KC_RETURN,    // Enter on main keyboard
	//OIS::KeyCode::KC_LCONTROL,
	//OIS::KeyCode::KC_A,
	//OIS::KeyCode::KC_S,
	//OIS::KeyCode::KC_D,
	//OIS::KeyCode::KC_F,
	//OIS::KeyCode::KC_G,
	//OIS::KeyCode::KC_H,
	//OIS::KeyCode::KC_J,
	//OIS::KeyCode::KC_K,
	//OIS::KeyCode::KC_L,
	//OIS::KeyCode::KC_SEMICOLON,
	//OIS::KeyCode::KC_APOSTROPHE,
	//OIS::KeyCode::KC_GRAVE,    // accent
	//OIS::KeyCode::KC_LSHIFT,
	//OIS::KeyCode::KC_BACKSLASH,
	//OIS::KeyCode::KC_Z,
	//OIS::KeyCode::KC_X,
	//OIS::KeyCode::KC_C,
	//OIS::KeyCode::KC_V,
	//OIS::KeyCode::KC_B,
	//OIS::KeyCode::KC_N,
	//OIS::KeyCode::KC_M,
	//OIS::KeyCode::KC_COMMA,
	//OIS::KeyCode::KC_PERIOD,    // . on main keyboard
	//OIS::KeyCode::KC_SLASH,    // / on main keyboard
	//OIS::KeyCode::KC_RSHIFT,
	//OIS::KeyCode::KC_MULTIPLY,    // * on numeric keypad
	//OIS::KeyCode::KC_LMENU,    // left Alt
	//OIS::KeyCode::KC_SPACE,
	//OIS::KeyCode::KC_CAPITAL,
	//OIS::KeyCode::KC_F1,
	//OIS::KeyCode::KC_F2,
	//OIS::KeyCode::KC_F3,
	//OIS::KeyCode::KC_F4,
	//OIS::KeyCode::KC_F5,
	//OIS::KeyCode::KC_F6,
	//OIS::KeyCode::KC_F7,
	//OIS::KeyCode::KC_F8,
	//OIS::KeyCode::KC_F9,
	//OIS::KeyCode::KC_F10,
	//OIS::KeyCode::KC_NUMLOCK,
	//OIS::KeyCode::KC_SCROLL,     // Scroll Lock
	//OIS::KeyCode::KC_NUMPAD7,
	//OIS::KeyCode::KC_NUMPAD8,
	//OIS::KeyCode::KC_NUMPAD9,
	//OIS::KeyCode::KC_SUBTRACTA,    // - on numeric keypad
	//OIS::KeyCode::KC_NUMPAD4,
	//OIS::KeyCode::KC_NUMPAD5,
	//OIS::KeyCode::KC_NUMPAD6,
	//OIS::KeyCode::KC_ADD,    // + on numeric keypad
	//OIS::KeyCode::KC_NUMPAD1,
	//OIS::KeyCode::KC_NUMPAD2,
	//OIS::KeyCode::KC_NUMPAD3,
	//OIS::KeyCode::KC_NUMPAD0,
	//OIS::KeyCode::KC_DECIMAL,    // . on numeric keypad
	//OIS::KeyCode::KC_OEM_102,    // < > | on UK/Germany keyboards
	//OIS::KeyCode::KC_F11,
	//OIS::KeyCode::KC_F12,
	//OIS::KeyCode::KC_F13,    //                     (NEC PC98)
	//OIS::KeyCode::KC_F14,    //                     (NEC PC98)
	//OIS::KeyCode::KC_F15,    //                     (NEC PC98)
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
	//OIS::KeyCode::KC_DIVIDE,    // / on numeric keypad
	//OIS::KeyCode::KC_SYSRQ,
	//OIS::KeyCode::KC_RMENU,    // right Alt
	//OIS::KeyCode::KC_PAUSE,    // Pause
	//OIS::KeyCode::KC_HOME,    // Home on arrow keypad
	//OIS::KeyCode::KC_UP,    // UpArrow on arrow keypad
	//OIS::KeyCode::KC_PGUP,    // PgUp on arrow keypad
	//OIS::KeyCode::KC_LEFT,    // LeftArrow on arrow keypad
	//OIS::KeyCode::KC_RIGHT,    // RightArrow on arrow keypad
	//OIS::KeyCode::KC_END,    // End on arrow keypad
	//OIS::KeyCode::KC_DOWN,    // DownArrow on arrow keypad
	//OIS::KeyCode::KC_PGDOWN,    // PgDn on arrow keypad
	//OIS::KeyCode::KC_INSERT,    // Insert on arrow keypad
	//OIS::KeyCode::KC_DELETE,    // Delete on arrow keypad
	//OIS::KeyCode::KC_LWIN,    // Left Windows key
	//OIS::KeyCode::KC_RWIN,    // Right Windows key
	//OIS::KeyCode::KC_APPS,    // AppMenu key
	//OIS::KeyCode::KC_POWER,    // System Power
	//OIS::KeyCode::KC_SLEEP,    // System Sleep
	//OIS::KeyCode::KC_WAKE,    // System Wake
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


class TWindow;

class TGON_API TInputModule :
	public IModule,
	public OIS::KeyListener, 
	public OIS::MouseListener, 
	public OIS::JoyStickListener
{
public:
	enum SupportInput
	{
		kMouse = 1,
		kKeyboard = 2,
		kJoystick = 4,
		kMultiTouch = 8,
		kTablet = 16,
	};


/*
	Generator
*/
	TGON_OBJECT( TInputModule, IModule )


/*
	Cons/Destructor
*/
public:
	/*
	*/
	//
	// Constructor
	// Initialize input module.
	//
	// @param inputAcceptTargets 
	// @param supportInputBits Input device flags what you want to use
	//
	TInputModule( TWindow* inputAcceptTargets, int32_t supportInputBits );

	//
	// Destructor
	//
	virtual ~TInputModule( );


/*
	Commands
*/
public:
	//
	virtual void Update( );


/*
	Gets
*/
	//
	//
	//
	// @return
	//
	uint32_t GetKeyboardNum( ) const;
	
	//
	//
	//
	// @return
	uint32_t GetMouseNum( ) const;

	//
	//
	//
	// @return
	//
	uint32_t GetJoyStickNum( ) const;

	//
	// Returns true while the user holds down the key identified by name.
	//
	bool GetKey( KeyCode keyCode ) const;

	//
	// Returns true during the frame the user releases the key identified by name.
	//
	bool GetKeyUp( KeyCode keyCode ) const;

	//
	// Returns true during the frame the user starts pressing down the key identified by name.
	//
	bool GetKeyDown( KeyCode keyCode ) const
	{
	}




/*
	Event handlers
*/
private:
	/*
		Keyboards
	*/
	virtual bool keyPressed( const OIS::KeyEvent& arg ) override
	{
		TConsole::Get( ).WriteLine( "keyPressed" );

		//std::cout << " KeyPressed {" << arg.key
		//	<< ", " << ((Keyboard*)(arg.device))->getAsString(arg.key)
		//	<< "} || Character (" << (char)arg.text << ")" << std::endl;
		return true;
	}

	virtual bool keyReleased( const OIS::KeyEvent& arg ) override
	{
		TConsole::Get( ).WriteLine( "keyReleased" );
		//if( arg.key == KC_ESCAPE || arg.key == KC_Q )
		//	appRunning = false;
		//std::cout << "KeyReleased {" << ((Keyboard*)(arg.device))->getAsString(arg.key) << "}\n";
		return true;
	}

	/*
		Mouses
	*/
	virtual bool mouseMoved( const OIS::MouseEvent& arg ) override
	{
		TConsole::Get( ).WriteLine( "mouseMoved" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouseMoved: Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}
	
	virtual bool mousePressed( const OIS::MouseEvent& arg, OIS::MouseButtonID id ) override
	{
		TConsole::Get( ).WriteLine( "mousePressed" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouse button #" << id << " pressed. Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}
	
	virtual bool mouseReleased( const OIS::MouseEvent& arg, OIS::MouseButtonID id ) override
	{
		TConsole::Get( ).WriteLine( "mouseReleased" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouse button #" << id << " released. Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}

	/*
		JoySticks
	*/
	virtual bool buttonPressed( const OIS::JoyStickEvent& arg, int button ) override
	{
	//	std::cout << std::endl << arg.device->vendor() << ". Button Pressed # " << button;
		return true;
	}
	
	virtual bool buttonReleased( const OIS::JoyStickEvent& arg, int button ) override
	{
	//	std::cout << std::endl << arg.device->vendor() << ". Button Released # " << button;
		return true;
	}
	
	virtual bool axisMoved( const OIS::JoyStickEvent& arg, int axis ) override
	{
	//	//Provide a little dead zone
	//	if( arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500 )
	//		std::cout << std::endl << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;
		return true;
	}

	virtual bool povMoved( const OIS::JoyStickEvent& arg, int pov ) override
	{
	//	std::cout << std::endl << arg.device->vendor() << ". POV" << pov << " ";
	//
	//	if( arg.state.mPOV[pov].direction & Pov::North ) //Going up
	//		std::cout << "North";
	//	else if( arg.state.mPOV[pov].direction & Pov::South ) //Going down
	//		std::cout << "South";
	//
	//	if( arg.state.mPOV[pov].direction & Pov::East ) //Going right
	//		std::cout << "East";
	//	else if( arg.state.mPOV[pov].direction & Pov::West ) //Going left
	//		std::cout << "West";
	//
	//	if( arg.state.mPOV[pov].direction == Pov::Centered ) //stopped/centered out
	//		std::cout << "Centered";
		return true;
	}
	//
	//bool vector3Moved( const OIS::JoyStickEvent &arg, int index)
	//{
	//	return true;
	//}


/*
	Internal works
*/
private:
	void CreateInputManager( TWindow* inputAcceptTargets );

	void SetupInputDevice( int32_t supportInputBits );


/*
	Private variables
*/
private:
	OIS::InputManager* m_inputManager;

	OIS::Keyboard* m_keyboardDevice;

	OIS::Mouse* m_mouseDeivece;

	OIS::JoyStick* m_joyStickDevice[4];

	char m_buffer[OIS::KeyCode::KC_MEDIASELECT+1];
};


inline uint32_t tgon::TInputModule::GetKeyboardNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISKeyboard );
}

inline uint32_t TInputModule::GetMouseNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISMouse );
}

inline uint32_t TInputModule::GetJoyStickNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISJoyStick );
}


}