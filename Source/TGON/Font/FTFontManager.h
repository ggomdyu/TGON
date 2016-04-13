/*
* Author : Junho-Cha
* Date : 2016-01-14
* Latest author :
* Latest date :
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