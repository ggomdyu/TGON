#include "PrecompiledHeader.pch"
#include "InputModule.h"

#include <string>
#include <boost/predef/os.h>

#include "Core/Platform/Window.h"

namespace tgon
{

InputModule::InputModule(platform::Window* inputAcceptTargets, uint32_t supportInputFlag) :
    m_inputManager(nullptr),
    m_keyboardDevice(nullptr),
    m_mouseDeivece(nullptr),
    m_joyStickDevice{0}
{
    this->InitializeInputManager(inputAcceptTargets, supportInputFlag);
}

InputModule::~InputModule()
{
}

void InputModule::Update()
{
    if (m_keyboardDevice)
    {
        m_keyboardDevice->capture();

        if (!m_keyboardDevice->buffered())
        {
            //handleNonBufferedKeys( );
        }
    }

    if (m_mouseDeivece)
    {
        m_mouseDeivece->capture();

        if (!m_mouseDeivece->buffered())
        {
            //handleNonBufferedMouse( );
        }
    }

    //if ( m_joyStickDevice )
    //{
    //
    //}
}

void InputModule::InitializeInputManager(platform::Window* inputAcceptWindow, uint32_t supportInputFlag)
{
    // OS dependent codes are here
    OIS::ParamList paramList;
    {
#if BOOST_PLATFORM_WINDOWS
        std::string wndHandleStr = std::to_string(reinterpret_cast<size_t>(inputAcceptWindow->GetWindowHandle()));

        paramList.insert({ "WINDOW", wndHandleStr.c_str() });
        paramList.insert({ "w32_mouse", "DISCL_FOREGROUND" });
        paramList.insert({ "w32_mouse", "DISCL_NONEXCLUSIVE" });
        paramList.insert({ "w32_keyboard", "DISCL_FOREGROUND" });
        paramList.insert({ "w32_keyboard", "DISCL_NONEXCLUSIVE" });
#endif
    }

    try
    {
        // This never returns null.
        // it will raise an exception on errors
        m_inputManager = OIS::InputManager::createInputSystem(paramList);

        // Lets enable all addons that were compiled in:
        m_inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);
    }
    catch (OIS::Exception)
    {
        std::abort();
    }


    this->SetupInputDevice(supportInputFlag);
}

void InputModule::SetupInputDevice(uint32_t supportInputFlag)
{
    if (supportInputFlag & InputSupport::Mouse)
    {
        m_mouseDeivece = static_cast<decltype(m_mouseDeivece)>(
            m_inputManager->createInputObject(OIS::OISMouse, true));

        m_mouseDeivece->setEventCallback(this);
    }

    if (supportInputFlag & InputSupport::Keyboard)
    {
        m_keyboardDevice = static_cast<decltype(m_keyboardDevice)>(
            m_inputManager->createInputObject(OIS::OISKeyboard, true));

        m_keyboardDevice->setEventCallback(this);
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


}