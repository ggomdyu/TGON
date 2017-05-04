/**
 * @filename    WindowsConsole.h
 * @author   ggomdyu
 * since    01/24/2016
 */

#pragma once
#include "../Generic/GenericConsole.h"

namespace tgon {

class TGON_API WindowsConsole : 
	public GenericConsole
{
/**
 * @section Ctor/Dtor
 */
public:
    WindowsConsole() = delete;
    ~WindowsConsole() = delete;
};

using TConsole = WindowsConsole;

} /* namespace tgon */