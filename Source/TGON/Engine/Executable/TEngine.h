/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/Config/Build.h"

#include "../../Core/Object/TEventSubject.h"


namespace tgon
{


class TGameBody;

class TGON_API TEngine :
	public TEventSubject
{
	/*
		Commands
	*/
public:
	int32_t Execute( int argc, char** argv );
	

	/*
		Cons/Destructor
	*/
public:
	//
	// Constructor
	//
	TEngine( );

	//
	// Destructor
	//
	virtual ~TEngine( ) = default;


	/*
		Private variables
	*/
private:
	std::shared_ptr<TGameBody> m_mainGameBody;
};


};
