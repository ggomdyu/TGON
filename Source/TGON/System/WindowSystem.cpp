#include "PrecompiledHeader.h"
#include "WindowSystem.h"



tgon::WindowSystem::WindowSystem( ) :
	TObject( "WindowSystem", nullptr )
{
}


tgon::WindowSystem::~WindowSystem( )
{
}


const tgon::SpTWindow tgon::WindowSystem::GetWindow( const std::wstring & wndName )
{
	auto findIter = m_wndRepo.find( wndName );
	if ( findIter != m_wndRepo.end( ))
	{
		return findIter->second;
	}

	return nullptr;
}