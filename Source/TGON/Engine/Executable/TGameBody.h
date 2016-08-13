/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Core/Object/TEventSubject.h"


#define TGON_GENERATE_GAMEAPP( className )\
std::shared_ptr<tgon::TGameApplication> GenerateGameApplication( )\
{\
	return std::make_shared<className>( );\
}

namespace tgon
{


class TGON_API TGameApplication :
	public TEventSubject
{
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TGameApplication, TEventSubject )


/*
	Cons/Destructor
*/
public:
	explicit TGameApplication( );

	virtual ~TGameApplication( );


/*
	Commands
*/
public:
	//
	// @note Update the frame
	//
	void Update( );


/*
	Sets
*/
	//
	// @note Play the game application's frame update ( Use on paused )
	//
	void Play( );
	
	//
	// @note Pause the game application's frame update
	//
	void Pause( );


/*
	Gets
*/
	bool IsPaused( ) const;


/*
	Private variables
*/
private:
	bool m_paused;
};


inline void TGameApplication::Play( )
{
	m_paused = false;
}

inline void tgon::TGameApplication::Pause( )
{
	m_paused = true;
}

inline bool tgon::TGameApplication::IsPaused( ) const
{
	return m_paused;
}



}