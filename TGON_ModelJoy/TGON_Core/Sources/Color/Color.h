#pragma once
#include <iostream>

namespace tgon
{
	/*union Color_RGBA;
	union Color_ARGB;*/

	enum ColorTable : uint32_t
	{
		Red =			0xffff0000,
		Green =		0xff00ff00,
		Blue =		0xff0000ff,
		Magenta =	0xffff00ff,
		Yellow =		0xffffff00,
		Cyan =		0xff00ffff,

		White =		0xffffffff,
		Black =		0xff000000,
	};

	union Color_ARGB
	{
	public:
		Color_ARGB( uint32_t _color = 0 ) :
			color( _color ) {}
		Color_ARGB( unsigned char _a, unsigned char _r,
							unsigned char _g, unsigned char _b ) :
					a( _a ), r( _r ), g( _g ), b( _b ) {}

		operator uint32_t( ) const { return color; }


	public:
		void		Inverse( )		{ r = 255-r; g = 255-g; b = 255-b; }


		struct {
			unsigned char a, r, g, b;
		};

	private:
		unsigned int color;
	};


	//union Color_RGBA
	//{
	//	Color_RGBA( uint32_t _color = 0 ) :
	//		color( _color ) {}
	//	Color_RGBA( unsigned char _r, unsigned char _g,
	//						unsigned char _b, unsigned char _a ) :
	//				r( _r ), g( _g ), b( _b ), a( _a ) {}

	//	operator uint32_t( ) const { return color; }
	//	inline operator Color_ARGB( ) const;

	//	enum ColorTable : uint32_t
	//	{
	//		Red =			0xff0000ff,
	//		Green =		0x00ff00ff,
	//		Blue =		0x0000ffff,
	//		Magenta =	0xff00ffff,
	//		Yellow =		0xffff00ff,
	//		Cyan =		0x00ffffff,

	//		White =		0xffffffff,
	//		Black =		0x000000ff,
	//	};

	//	struct {
	//		unsigned char a, b, g, r;
	//	};

	//private:
	//	unsigned int color;
	//};

	//inline Color_ARGB::operator Color_RGBA( ) const
	//{
	//	return Color_RGBA( r, g, b, a );
	//}

	//inline Color_RGBA::operator Color_ARGB( ) const
	//{
	//	return Color_ARGB( a, r, g, b );
	//}
}