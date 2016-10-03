#include "PrecompiledHeader.h"
#include "Random.h"


#define W 32
#define R 16
#define P 0
#define M1 13
#define M2 9
#define M3 5

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define MAT3NEG(t,v) (v<<(-(t)))
#define MAT4NEG(t,b,v) (v ^ ((v<<(-(t))) & b))

#define V0            STATE[state_i                   ]
#define VM1           STATE[(state_i+M1) & 0x0000000fU]
#define VM2           STATE[(state_i+M2) & 0x0000000fU]
#define VM3           STATE[(state_i+M3) & 0x0000000fU]
#define VRm1          STATE[(state_i+15) & 0x0000000fU]
#define VRm2          STATE[(state_i+14) & 0x0000000fU]
#define newV0         STATE[(state_i+15) & 0x0000000fU]
#define newV1         STATE[state_i                 ]
#define newVRm1       STATE[(state_i+14) & 0x0000000fU]

#define FACT 2.32830643653869628906e-10

namespace
{


uint32_t state_i = 0;
uint32_t STATE[R];

struct WELLRNGHelper
{
	WELLRNGHelper( )
	{
		state_i = 0;
		uint32_t init[R];
		for ( int32_t j = 0; j < R; j++ )
			STATE[j] = init[j];
	}
} g_wi;


} /* namespace { */


namespace tgon
{


float Random::WELLRNG512a( )
{
	uint32_t z0, z1, z2;

	z0 = VRm1;
	z1 = MAT0NEG( -16, V0 )^MAT0NEG( -15, VM1 );
	z2 = MAT0POS( 11, VM2 );
	newV1 = z1^z2;
	newV0 = MAT0NEG( -2, z0 )^MAT0NEG( -18, z1 )^MAT3NEG( -28, z2 )^MAT4NEG( -5, 0xda442d24U, newV1 );
	state_i = ( state_i+15 )&0x0000000fU;

	return static_cast<float>( STATE[state_i]*FACT );
}

int Random::Range( int min, int max )
{
	// TODO: 코드가 약간 이상함
	return min + ( static_cast<int>( WELLRNG512a( ))*( max-min ));
}

float Random::Range( float min, float max )
{
	return min + ( WELLRNG512a( )*( max-min ));
}


} /*namespace tgon*/