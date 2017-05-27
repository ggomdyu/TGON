/*
* Author : Junho-Cha
* Date : 01/14/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "FTFontManager.h"


namespace tgon {


enum AlignTable
{
	FT_LEFT		= 0,
	FT_CENTER	= 0x1,
	FT_RIGHT	= 0x2,
	FT_TOP		= 0x4,
	FT_VCENTER	= 0x8,
};

enum ThicknessTable
{
	FT_NORMAL,
	FT_BOLD
};


class FTFontFace
{
public:
	FTFontFace( const char* fontPath, int32_t size );
	~FTFontFace( );

	operator	FT_Face( ) const		{ return m_face; }

public:
	int32_t			GetHeight( ) const		{ return m_size; }
	FT_Face	GetFace( ) const		{ return m_face; }

private:
	FT_Face m_face;

	bool m_isKerning;
	int32_t m_size;
};


}