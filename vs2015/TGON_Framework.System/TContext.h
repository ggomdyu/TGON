/*
* Author : Junho-Cha
* Date : 05/18/2015
* Latest author : 
* Latest date : 
*/


#pragma once
#include <System/ISystem.h>
#include <Core/TObject.h>
#include <Config/Build.h>

namespace tgon
{


class TGON_API TContext : 
	public ISystem
{
public:
	TContext( );
	~TContext( );

	void RegisterSystem( ISystem* system );
};


}