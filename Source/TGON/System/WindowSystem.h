/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include <map>
#include "../Core/TObject.h"
#include "../System/ISystem.h"
#include "../Core/TSingleton.h"
#include "../Platform/Window/TWindow.h"


namespace tgon
{


class WindowSystem : 
	public ISystem
{
public:
	TGON_OBJECT( WindowSystem, ISystem )
	TGON_SINGLETON( WindowSystem )

	using WindowRepo = std::map<std::wstring, WpTWindow>;
public:
	using iterator = WindowRepo::iterator;
	using const_iterator = WindowRepo::const_iterator;

public:
	virtual void Update( float tickTime ) override;
	
	void AddWindow( const SpTWindow& window );
	const WpTWindow& GetWindow( const std::wstring& wndName );
	
	iterator begin( );
	iterator end( );

protected:
	WindowSystem( );
	virtual ~WindowSystem( );

private:
	WindowRepo m_wndRepo;
};


inline void WindowSystem::AddWindow(
	const SpTWindow& window )
{
	wchar_t caption[256] {0};
	window->GetCaption( caption );

	m_wndRepo[caption] = window;
}

inline const tgon::WpTWindow& tgon::WindowSystem::GetWindow(
	const std::wstring& wndName )
{
	return m_wndRepo[wndName.c_str()];
}

inline void tgon::WindowSystem::Update( float tickTime )
{
}

inline WindowSystem::iterator tgon::WindowSystem::begin( )
{
	return m_wndRepo.begin( );
}

inline WindowSystem::iterator tgon::WindowSystem::end( )
{
	return m_wndRepo.end( );
}


}