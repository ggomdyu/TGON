/*
* 작성자 : 차준호
* 작성일 : 2016-01-03
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <iostream>

namespace tgon
{
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
		uint32_t color;
	};
}