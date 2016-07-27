/*
* Author : Cha Jnho
* Date : 07/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/Window/TWindow.h"
#include "../../Core/Object/TEventSubject.h"
#include "../../RenderCore/Graphics/TGraphics.h"
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
public:
	/*
		Cons/Destructor
	*/
	explicit TGameBody( const WindowStyle& wndStyle );

	virtual ~TGameBody( );

public:
	/*
		Commands
	*/
	// Main function calls this directly. These arguments will be parsed 
	virtual void Update( );

	virtual void Render( );


	/*
		Gets
	*/
	const SpTWindow& GetWindow( ) const;

	const SpTGraphics& GetGraphics( ) const;

	//template <typename ModuleTy>
	//const std::shared_ptr<ModuleTy>& GetModule( ) const;


private:
	// Initialize all of modules for game play
	void InitializeModule( );


private:
	bool m_isGameDone;

	SpTWindow m_window;

	SpTGraphics m_graphics;

	std::map<uint32_t, std::shared_ptr<IModule>> m_modules;
};


inline const SpTWindow & tgon::TGameBody::GetWindow( ) const
{
	return m_window;
}

inline const SpTGraphics& TGameBody::GetGraphics( ) const
{
	return m_graphics;
}


}