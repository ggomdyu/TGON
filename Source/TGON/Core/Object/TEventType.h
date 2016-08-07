/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/Config/Build.h"


namespace tgon
{


class /*TGON_API*/ TEventType
{
	explicit TEventType( const char* eventName );

	uint32_t operator( );

private:
	uint32_t m_eventNameHash;
};
