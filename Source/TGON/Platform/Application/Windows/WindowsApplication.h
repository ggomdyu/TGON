/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Platform dependent API Sets for Windows
*/


#pragma once
#include "../../Config/Build.h"
#include "../Abstract/AbstractApplication.h"

namespace tgon
{


class WindowsApplication;
using ApplicationImpl = WindowsApplication;

class TGON_API WindowsApplication :
	public AbstractApplication
{
public:
	static void EnableVisualStyles( );

private:
	WindowsApplication( ) = delete;
	virtual ~WindowsApplication( ) = delete;
};


}