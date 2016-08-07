/*
* Author : Cha Junho
* Date : 07/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "Interface/IModule.h"


namespace tgon
{


class TGON_API TimeModule :
	public IModule
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TimeModule, IModule )

public:
	/*
		Cons/Destructor
	*/
	TimeModule( );

	virtual ~TimeModule( ) = 0;


	//float GetElapsedTime( ) const;


public:
	/*
		Commands
	*/
	virtual void Update( ) {};


private:
	//float m_oldTime;
};



}