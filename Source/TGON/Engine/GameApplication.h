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


class IGameApplicationEventHandler
{
public:
	virtual ~IGameApplicationEventHandler( ) = default;

	virtual void OnUpdate( ) = 0;
	virtual void OnRender( ) = 0;
};

class TGON_API GameApplication :
	public Object,
	public IGameApplicationEventHandler
{
/**
 * Generator
 */ 
public:
	TGON_GENERATE_OBJECT_INTERFACE( GameApplication )

/**
 * Ctor/Dtor
 */ 
public:
	/* note Create default window, no custom event handler, by WindowStyle */
	explicit GameApplication( const std::shared_ptr<WindowFrame>& window );
	virtual ~GameApplication( ) = default;

/**
 * Sets
 */ 
	/* @note Play the game application's frame update ( Use on paused ) */
	void Play( );
	/* @note Pause the game application's frame update */
	void Pause( );

/**
 * Gets
 */ 
	const std::shared_ptr<WindowFrame>& GetRootWindow( ) const;
	bool IsPaused( ) const;

/**
 * Private variables
 */ 
private:
	bool m_paused;

	std::shared_ptr<WindowFrame> m_rootWindow;
};


inline void GameApplication::Play( )
{
	m_paused = false;
}

inline void tgon::GameApplication::Pause( )
{
	m_paused = true;
}

inline const std::shared_ptr<WindowFrame>& GameApplication::GetRootWindow( ) const
{
	return m_rootWindow;
}

inline bool tgon::GameApplication::IsPaused( ) const
{
	return m_paused;
}


}