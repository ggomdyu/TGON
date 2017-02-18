/**
 * author   ggomdyu
 * since    07/24/2016


 */

#pragma once
#include "Interface/IModule.h"
#include "Typedef/KeyCode.h"

#include <cstdint>
#include <OISInputManager.h>
#include <OISException.h>		// Not used
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISEvents.h>

#include "../../Core/Platform/OSAL/PlatformWindow.h"


namespace tgon
{


struct InputSupport
{
	enum : uint32_t
	{
		Mouse = 1,
		Keyboard = 2,
		Joystick = 4,
		MultiTouch = 8,
		Tablet = 16,
	};
};


class TGON_API InputModule :
	public IModule,
	public OIS::KeyListener,
	public OIS::MouseListener,
	public OIS::JoyStickListener
{
/**
 * Generator
 */
public:
	TGON_GENERATE_OBJECT_INTERFACE( InputModule )

/**
 * Ctor/Dtor
 */
public:
	/**
	 * @note Initialize input system using OIS.
	 * @param inputAcceptWindow The window which you want to receive input message
	 * @param supportInputBits Alert input system to use ( ex: InputSupport::Keyboard | InputSupport::Mouse )
	 */
	InputModule( WindowFrame* inputAcceptWindow, uint32_t supportInputFlag );
	virtual ~InputModule( );

/**
 * Commands
 */
public:
	//
	virtual void Update( );

/**
 * Gets
 */
public:
	/* @return	*/
	uint32_t GetKeyboardNum( ) const;
	
	/* @return	*/
	uint32_t GetMouseNum( ) const;

	/* @return	*/
	uint32_t GetJoyStickNum( ) const;

	/* @return	true while the user holds down the key identified by name */
	bool GetKey( KeyCode keyCode ) const
	{
		return false;
	}

	/* @return	true during the frame the user releases the key identified by name. */
	bool GetKeyUp( KeyCode keyCode ) const
	{
		return false;
	}

	/* @return	true during the frame the user starts pressing down the key identified by name. */
	bool GetKeyDown( KeyCode keyCode ) const
	{
		return false;
	}

/**
 * Event handlers
 */
private:
	// Keyboards
	virtual bool keyPressed( const OIS::KeyEvent& arg ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "keyPressed" );

		//std::cout << " KeyPressed {" << arg.key
		//	<< ", " << ((Keyboard*)(arg.device))->getAsString(arg.key)
		//	<< "} || Character (" << (char)arg.text << ")" << std::endl;
		return true;
	}

	virtual bool keyReleased( const OIS::KeyEvent& arg ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "keyReleased" );
		//if( arg.key == KC_ESCAPE || arg.key == KC_Q )
		//	appRunning = false;
		//std::cout << "KeyReleased {" << ((Keyboard*)(arg.device))->getAsString(arg.key) << "}\n";
		return true;
	}

	// Mouses
	virtual bool mouseMoved( const OIS::MouseEvent& arg ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "mouseMoved" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouseMoved: Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}
	
	virtual bool mousePressed( const OIS::MouseEvent& arg, OIS::MouseButtonID id ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "mousePressed" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouse button #" << id << " pressed. Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}
	
	virtual bool mouseReleased( const OIS::MouseEvent& arg, OIS::MouseButtonID id ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "mouseReleased" );
		//const OIS::MouseState& s = arg.state;
		//std::cout << "\nMouse button #" << id << " released. Abs("
		//		  << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
		//		  << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
		return true;
	}

	// JoySticks
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
	void InitializeInputManager( WindowFrame* inputAcceptWindow, uint32_t supportInputFlag );

	void SetupInputDevice( uint32_t supportInputFlag );


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


inline uint32_t tgon::InputModule::GetKeyboardNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISKeyboard );
}

inline uint32_t InputModule::GetMouseNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISMouse );
}

inline uint32_t InputModule::GetJoyStickNum( ) const
{
	return m_inputManager->getNumberOfDevices( OIS::OISJoyStick );
}


} /*namespace tgon*/