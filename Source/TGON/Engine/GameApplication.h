/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Engine/EngineContextObject.h"
#include "../Core/Platform/PlatformWindow.h"


#define TGON_GENERATE_GAMEAPP( className )\
namespace tgon {\
	std::shared_ptr<tgon::GameApplication> GenerateGameApplication( )\
	{\
		return std::make_shared<className>( );\
	}\
}

namespace tgon
{


class AGameApplicationEventHandler
{
public:
	/* @note Update the frame */
	virtual void OnUpdate( ) {};
	virtual void OnRender( ) {};
	virtual void OnDestroy( ) {};
};

class TGON_API GameApplication :
	public ModuleContext,
	public AGameApplicationEventHandler
{
	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( GameApplication, ModuleContext )

	// 
	// Ctor/Dtor
	// 
public:
	/* note Create default window, no custom event handler, by WindowStyle */
	explicit GameApplication( const std::shared_ptr<TWindowFrame>& window ) :
		m_paused( false ),
		m_rootWindow( window )
	{
	}
	virtual ~GameApplication( ) = default;

	// 
	// Sets
	// 
	/* @note Play the game application's frame update ( Use on paused ) */
	void Play( );
	/* @note Pause the game application's frame update */
	void Pause( );

	// 
	// Gets
	// 
	const std::shared_ptr<TWindowFrame>& GetRootWindow( ) const;
	bool IsPaused( ) const;

	// 
	// Private variables
	// 
private:
	bool m_paused;
	std::shared_ptr<TWindowFrame> m_rootWindow;
};


inline void GameApplication::Play( )
{
	m_paused = false;
}

inline void tgon::GameApplication::Pause( )
{
	m_paused = true;
}

inline const std::shared_ptr<TWindowFrame>& GameApplication::GetRootWindow( ) const
{
	return m_rootWindow;
}

inline bool tgon::GameApplication::IsPaused( ) const
{
	return m_paused;
}


}