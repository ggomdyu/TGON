/*
* Author : Cha Junho
* Date : 07/23/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once


#define TGON_REGISTER_MAIN( className )\
int32_t RunAppMain( int32_t argc, char** argv )\
{\
	return className::Main( argc, argv );\
}