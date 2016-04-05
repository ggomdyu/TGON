/*
* 작성자 : 차준호
* 작성일 : 2016-01-14
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <Pattern/Singleton.h>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace tgon {

class FTFontManager
{
public:
	static FTFontManager* GetInstance( )
	{
		static FTFontManager ftInst;
		return &ftInst;
	}

public:
	FT_Library GetFTLibrary( ) const { return library; }


private:
	FTFontManager( );
	~FTFontManager( );

private:
	FT_Library library;
};


inline FTFontManager* GetFTFontManager( ) { return FTFontManager::GetInstance( ); }


}