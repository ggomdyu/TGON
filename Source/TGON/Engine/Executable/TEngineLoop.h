/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Core/Object/TEventSubject.h"


namespace tgon
{


class TGameBody;

class TGON_API TEngineLoop :
	public TEventSubject
{
public:
	TGON_OBJECT( TEngineLoop, TEventSubject )

	/*
		Cons/Destructor
	*/
	TEngineLoop( );

	virtual ~TEngineLoop( ) = default;


public:
	/*
		Commands
	*/
	int32_t Execute( int argc, char** argv );


private:
	/*
		Internal works
	*/
	void ParseCommandLine( ) {}

	void OnDestroy( );


private:
	bool m_isGameDone;

	std::shared_ptr<TGameBody> m_gameBody;
};


inline void TEngineLoop::OnDestroy( )
{
	m_isGameDone = true;
}


};
