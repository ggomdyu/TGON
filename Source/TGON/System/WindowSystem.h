/*
* 작성자 : 차준호
* 작성일 : 2016-04-02
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <map>
#include "../Config/Compiler/SyntaxCompatible.hpp"
#include "../Window/TWindow.h"
#include "../Object/TObject.h"


namespace tgon
{


class WindowSystem final : public TObject
{
public:
	WindowSystem( );
	~WindowSystem( );

public:
	void AddWindow( const SpTWindow& );
	const SpTWindow GetWindow( const std::wstring& );

private:
	std::map<std::wstring, SpTWindow> m_wndRepo;
};



TGON_FORCEINLINE void WindowSystem::AddWindow( const SpTWindow& window )
{
	m_wndRepo.insert( std::make_pair(
			window->GetCaption( ).c_str( ),
			window ));
}



}