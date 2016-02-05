/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-14
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include <pattern\Singleton.h>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace tgon {

class FTFontManager
{
public:
	DECLARE_STATIC_SINGLETON( FTFontManager )

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