#include "PrecompiledHeader.h"

#include <cstdlib>
#include <ctime>

#include "WELL1024a.h"

#define W 32
#define R 32
#define M1 3
#define M2 24
#define M3 10

#define MAT0POS(t, v) (v ^ (v >> t))
#define MAT0NEG(t, v) (v ^ (v << (-(t))))
#define Identity(v) (v)

#define V0 STATE[state_i]
#define VM1 STATE[(state_i + M1) & 0x0000001fU]
#define VM2 STATE[(state_i + M2) & 0x0000001fU]
#define VM3 STATE[(state_i + M3) & 0x0000001fU]
#define VRm1 STATE[(state_i + 31) & 0x0000001fU]
#define newV0 STATE[(state_i + 31) & 0x0000001fU]
#define newV1 STATE[state_i]

#define FACT 2.32830643653869628906e-10

namespace tgon
{
namespace
{

thread_local unsigned int state_i;
thread_local unsigned int STATE[R];
thread_local unsigned int z0, z1, z2;

} /* namespace */

TGON_API void SrandWELL1024a()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < R; ++i)
    {
        STATE[i] = std::rand();
    }
}

TGON_API double WELL1024a()
{
    z0 = VRm1;
    z1 = Identity(V0) ^ MAT0POS(8, VM1);
    z2 = MAT0NEG(-19, VM2) ^ MAT0NEG(-14, VM3);
    newV1 = z1 ^ z2;
    newV0 = MAT0NEG(-11, z0) ^ MAT0NEG(-7, z1) ^ MAT0NEG(-13, z2);
    state_i = (state_i + 31) & 0x0000001fU;

    return static_cast<double>(STATE[state_i]) * FACT;
}

} /* namespace tgon */