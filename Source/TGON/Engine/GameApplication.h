/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Engine/EngineContextObject.h"

#include "../Core/Platform/OSAL/PlatformWindow.h"


#define TGON_GENERATE_GAMEAPP( className )\
namespace tgon {\
	std::shared_ptr<tgon::GameApplication> GenerateGameApplication( )\
	{\
		return std::make_shared<className>( );\
	}\
}

namespace tgon
{


class TGON_API GameApplication :
	public EngineContextObject
{
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( GameApplication, EngineContextObject )


	/*
		Ctor/Dtor
	*/
public:
	explicit GameApplication( const WindowStyle& wndStyle );

	virtual ~GameApplication( );


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
	const std::shared_ptr<TPlatformWindow>& GetRootWindow( ) const;

	bool IsPaused( ) const;


	/*
		Private variables
	*/
private:
	bool m_paused;

	std::shared_ptr<TPlatformWindow> m_rootWindow;
};


inline void GameApplication::Play( )
{
	m_paused = false;
}

inline void tgon::GameApplication::Pause( )
{
	m_paused = true;
}

inline const std::shared_ptr<TPlatformWindow>& GameApplication::GetRootWindow( ) const
{
	return m_rootWindow;
}

inline bool tgon::GameApplication::IsPaused( ) const
{
	return m_paused;
}


}