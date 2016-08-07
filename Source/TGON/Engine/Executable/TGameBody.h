/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <vector>

#include "../../Platform/Window/TWindow.h"
#include "../../Platform/Window/WindowStyle.h"
#include "../../Core/Object/TEventSubject.h"
#include "../../RenderCore/Graphics/TGraphicsDevice.h"
#include "../../RenderCore/Graphics/GraphicsProperty.h"
#include "../../Engine/Module/Interface/IModule.h"


#define TGON_GENERATE_GAMEBODY( className )\
std::shared_ptr<tgon::TGameBody> GenerateGameBody( )\
{\
	return std::make_shared<className>( );\
}

namespace tgon
{


class TGON_API TGameBody :
	public TEventSubject
{
/*
	Generator
*/
public:
	TGON_OBJECT( TGameBody, TEventSubject )

public:
/*
	Cons/Destructor
*/
	//
	// Constructor
	//
	// @param wndStyle
	// @param graphicsProp
	//
	explicit TGameBody( const WindowStyle& wndStyle, const GraphicsProperty& graphicsProp );

	//
	// Destructor
	//
	virtual ~TGameBody( );


/*
	Commands
*/
public:
	void Update( );

	void Render( );


/*
	Sets
*/
	void Pause( bool enablePause );


/*
	Gets
*/
	TWindow* GetWindow( );

	//TGraphicsDeivce& GetGraphicsDevice( ) ;

	//
	bool IsPaused( ) const;

	template <typename ModuleTy>
	ModuleTy* GetModule( );


/*
	Internal works
*/
private:
	void SetupModule( );


/*
	Private variables
*/
private:

	std::map<uintptr_t, std::shared_ptr<IModule>> m_modules;

	// For fast iterating
	std::vector<std::shared_ptr<IModule>> m_modulesForUpdate;

	bool m_paused;

	TWindow m_window;
};


inline void tgon::TGameBody::Pause( bool enablePause )
{
	m_paused = enablePause;
}

inline TWindow* TGameBody::GetWindow( )
{
	return &m_window;
}

inline bool tgon::TGameBody::IsPaused( ) const
{
	return m_paused;
}


}