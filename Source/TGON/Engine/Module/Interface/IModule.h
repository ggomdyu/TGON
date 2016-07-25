/*
* Author : Cha Junho
* Date : 07/13/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Core/Object/TEventSubject.h"


namespace tgon
{


class TGON_API IModule :
	public TEventSubject
{
public:
	TGON_OBJECT( IModule, TEventSubject )

public:
	/*
		Cons/Destructor
	*/
	IModule( );

	virtual ~IModule( ) = 0;


public:
	/*
		Commands
	*/
	virtual void Update( ) {};
};



}