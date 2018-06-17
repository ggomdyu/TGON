/**
 * @filename    WindowsInputManager.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include "Core/Platform/Config.h"

namespace OIS
{

class Mouse;
class Keyboard;
class JoyStick;
class InputManager;
typedef std::multimap<std::string, std::string> ParamList;

} /* namespace OIS */

namespace tgon
{

class Window;

class TGON_API InputManagerImpl final
{
/* @section Public constructor */
public:
    explicit InputManagerImpl(std::shared_ptr<Window> inputTarget);
    
/* @section Public destructor */
public:
    ~InputManagerImpl();

/* @section Public method */
public:
    void Update();
    OIS::Mouse* CreateMouseDevice();
    OIS::Keyboard* CreateKeyboardDevice();
    OIS::JoyStick* CreateGamepadDevice();

/* @section Private method */
private:
    OIS::ParamList QueryParamList(std::shared_ptr<Window> inputTarget) const;
    
/* @section Protected variable */
protected:
    OIS::InputManager* m_inputManager;
};

} /* namespace tgon */
