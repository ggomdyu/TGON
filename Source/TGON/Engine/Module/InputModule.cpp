#include "PrecompiledHeader.h"
#include "InputModule.h"

#include "../../Platform/Window/TWindow.h"
#include <string>


tgon::TInputModule::TInputModule( TWindow* inputAcceptTargets, int32_t supportInputBits ) :
	m_inputManager( nullptr ),
	m_keyboardDevice( nullptr ),
	m_mouseDeivece( nullptr ),
	m_joyStickDevice{ 0 }
{
	this->CreateInputManager( inputAcceptTargets );

	this->SetupInputDevice( supportInputBits );
}

tgon::TInputModule::~TInputModule( )
{
}

void tgon::TInputModule::Update( )
{
	if ( m_keyboardDevice )
	{
		m_keyboardDevice->capture( );
	
		if ( !m_keyboardDevice->buffered( ))
		{
			//handleNonBufferedKeys( );
		}
	}

	if ( m_mouseDeivece )
	{
		m_mouseDeivece->capture( );

		if ( !m_mouseDeivece->buffered( ))
		{
			//handleNonBufferedMouse( );
		}
	}

	//if ( m_joyStickDevice )
	//{
	//
	//}
}

void tgon::TInputModule::CreateInputManager( TWindow* inputAcceptTargets )
{
	// Insert OS Specific Info here
	OIS::ParamList paramList;
	{
		const std::string wndHandleStr = std::to_string( reinterpret_cast<size_t>( 
			inputAcceptTargets->GetWindowHandle( )));

		paramList.insert({ "WINDOW", wndHandleStr.c_str( )});
		paramList.insert({ "w32_mouse", "DISCL_FOREGROUND" });
		paramList.insert({ "w32_mouse", "DISCL_NONEXCLUSIVE" });
		paramList.insert({ "w32_keyboard", "DISCL_FOREGROUND" });
		paramList.insert({ "w32_keyboard", "DISCL_NONEXCLUSIVE" });
	}

	try
	{
		// This never returns null.
		// it will raise an exception on errors
		m_inputManager = OIS::InputManager::createInputSystem( paramList );
	
		// Lets enable all addons that were compiled in:
		m_inputManager->enableAddOnFactory( OIS::InputManager::AddOn_All );
	}
	catch ( OIS::Exception )
	{
		std::abort( );
	}
}

void tgon::TInputModule::SetupInputDevice( int32_t supportInputBits )
{
	if ( supportInputBits & SupportInput::kMouse )
	{
		m_mouseDeivece = static_cast<decltype( m_mouseDeivece )>(
			m_inputManager->createInputObject( OIS::OISMouse, true ));
		m_mouseDeivece->setEventCallback( this );
	}

	if ( supportInputBits & SupportInput::kKeyboard )
	{
		m_keyboardDevice = static_cast<decltype( m_keyboardDevice )>( 
			m_inputManager->createInputObject( OIS::OISKeyboard, true ));
		m_keyboardDevice->setEventCallback( this );
	}

	//if ( supportBitsToInt & static_cast<Flags>( SupportInput::kJoystick ))
	//{
	//
	//}
}


//void handleNonBufferedKeys( )
//{
//	if ( g_kb->isKeyDown( KC_ESCAPE ) || g_kb->isKeyDown( KC_Q ) )
//		appRunning = false;
//
//	if ( g_kb->isModifierDown( Keyboard::Shift ) )
//		std::cout << "Shift is down..\n";
//	if ( g_kb->isModifierDown( Keyboard::Alt ) )
//		std::cout << "Alt is down..\n";
//	if ( g_kb->isModifierDown( Keyboard::Ctrl ) )
//		std::cout << "Ctrl is down..\n";
//}

//void handleNonBufferedMouse( )
//{
//	//Just dump the current mouse state
//	const MouseState &ms = g_m->getMouseState( );
//	std::cout << "\nMouse: Abs(" << ms.X.abs << " " << ms.Y.abs << " " << ms.Z.abs
//		<< ") B: " << ms.buttons << " Rel(" << ms.X.rel << " " << ms.Y.rel << " " << ms.Z.rel << ")";
//}