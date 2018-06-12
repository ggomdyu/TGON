/**
 * @filename    WindowsInputManagerFwd.h
 * @author      ggomdyu
 * @since       06/12/2018
 */

#pragma once
#include <map>

namespace tgon
{

class Window;

} /* namespace tgon */

namespace OIS
{

class Mouse;
class Keyboard;
class JoyStick;
class InputManager;
typedef std::multimap<std::string, std::string> ParamList;

} /* namespace OIS */