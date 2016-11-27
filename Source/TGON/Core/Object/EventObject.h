/**
 * Author : Cha Junho
 * Date : 07/10/2016
 * Latest author :
 * Latest date :
 */


#pragma once
#include "Object.h"
#include "Type.h"


namespace tgon
{

// TODO : DELETE IT!!
class TGON_API EventObject :
	public Object
{
	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( EventObject )

	// 
	// Ctor/Dtor
	// 
public:
	EventObject( ) = default;
	virtual ~EventObject( ) = default;
};


} /*namespace tgon*/

