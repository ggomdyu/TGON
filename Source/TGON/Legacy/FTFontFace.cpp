#include "PrecompiledHeader.h"
#include "FTFontFace.h"


tgon::FTFontFace::FTFontFace( const char* fontPath, int32_t size )
{
	// Get font face, not family
	FT_Error err = FT_New_Face( GetFTFontManager( )->GetFTLibrary( ),
								fontPath, 0, &m_face );
	if ( err != 0 )
	{
		abort( );
	}


	err = FT_Set_Pixel_Sizes( m_face, size, size );
	if ( err != 0 )
	{
		abort( );
	}

	m_isKerning = ( FT_HAS_KERNING( m_face ) > 0 );
}


tgon::FTFontFace::~FTFontFace( )
{
	FT_Done_Face( m_face );
}