/*
* Author : Cha Junho
* Date : 07/13/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Core/Object/EventObject.h"

#include <boost/noncopyable.hpp>


namespace tgon
{


class TGON_API IModule :
	public EventObject,
	private boost::noncopyable
{
	/*
		Generator
	*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( IModule, EventObject )


	/*
		Ctor/Dtor
	*/
public:
	IModule( );

	virtual ~IModule( ) = 0;


	/*
		Commands
	*/
public:
	virtual void Update( ) = 0;
};



}