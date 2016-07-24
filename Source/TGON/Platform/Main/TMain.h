/*
* Author : Cha Junho
* Date : 07/23/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once


#define TGON_REGISTER_MAINAPP( className )\
int32_t RunApplication( )\
{\
	return className::Main( );\
}