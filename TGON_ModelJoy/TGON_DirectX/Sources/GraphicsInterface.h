#pragma once
class GraphicsInterface
{
public:
	GraphicsInterface( );
	~GraphicsInterface( );

	virtual void Initialize( ) = 0;

	virtual void BeginDraw( ) = 0;
	virtual void EndDraw( ) = 0;
};

namespace Color {
	struct argb
	{
		union {
			struct {
				unsigned char a, r, g, b;
			};
		};

		argb( unsigned char _a = 0, unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0 ) :
					a( _a ), r( _r ), g( _g ), b( _b )
		{
		}

		//template <class T>
		//operator T( )
		//{
		//	return ((unsigned long)a << 24) | ((unsigned long)r << 16) | ((unsigned long)g << 8) | ((unsigned long)b);
		//}


		bool operator==( const argb& rhs )
		{
			if ( this == &rhs )
			{
				return true;
			}

			if ( a == rhs.a && r ==rhs.r &&
					g == rhs.g && b == rhs.b )
				return true;
			return false;
		}

		argb& operator+=( const argb& rhs )
		{
			a += rhs.a;
			r += rhs.b;
			g += rhs.g;
			b += rhs.b;

			return *this;
		}

		argb& operator-=( const argb& rhs )
		{
			a -= rhs.a;
			r -= rhs.b;
			g -= rhs.g;
			b -= rhs.b;

			return *this;
		}

		argb& operator*=( const argb& rhs )
		{
			a *= rhs.a;
			r *= rhs.b;
			g *= rhs.g;
			b *= rhs.b;

			return *this;
		}

		argb& operator/=( const argb& rhs )
		{
			a /= rhs.a;
			r /= rhs.b;
			g /= rhs.g;
			b /= rhs.b;

			return *this;
		}
	};
}