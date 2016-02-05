#include "stdafx.h"
#include "FTFontManager.h"


tgon::FTFontManager::FTFontManager( )
{
	FT_Init_FreeType( &library );
}


tgon::FTFontManager::~FTFontManager( )
{
	FT_Done_FreeType( library );
}