#include "PrecompiledHeader.h"
#include "WELLRNG.h"

#define W 32
#define R 16
#define P 0
#define M1 13
#define M2 9
#define M3 5

#define MAT0NEG(t, v) (v ^ (v << (-(t))))
#define MAT0POS(t, v) (v ^ (v >> t))
#define MAT3NEG(t, v) (v << (-(t)))
#define MAT4NEG(t, b, v) (v ^ ((v << (-(t))) & b))

#define V0 helper.STATE[helper.state_i]
#define VM1 helper.STATE[(helper.state_i + M1) & 0x0000000fU]
#define VM2 helper.STATE[(helper.state_i + M2) & 0x0000000fU]
#define VM3 helper.STATE[(helper.state_i + M3) & 0x0000000fU]
#define VRm1 helper.STATE[(helper.state_i + 15) & 0x0000000fU]
#define VRm2 helper.STATE[(helper.state_i + 14) & 0x0000000fU]
#define newV0 helper.STATE[(helper.state_i + 15) & 0x0000000fU]
#define newV1 helper.STATE[helper.state_i]
#define newVRm1 helper.STATE[(helper.state_i + 14) & 0x0000000fU]

#define FACT 2.32830643653869628906e-10

namespace {

struct TGON_API WELLRNGHelper
{
    uint32_t state_i;
    uint32_t STATE[R];

    WELLRNGHelper() :
        state_i(0)
    {
        uint32_t init[R];
        std::memmove(STATE, init, sizeof(uint32_t) * R);
    }
};

} /* namespace */

namespace tgon {
namespace random {

TGON_API float WELLRNG512a()
{
    thread_local WELLRNGHelper helper;

	uint32_t z0, z1, z2;

    z0 = VRm1;
    z1 = MAT0NEG(-16, V0) ^ MAT0NEG(-15, VM1);
    z2 = MAT0POS(11, VM2);
    newV1 = z1 ^ z2;
    newV0 = MAT0NEG(-2, z0) ^ MAT0NEG(-18, z1) ^ MAT3NEG(-28, z2) ^ MAT4NEG(-5, 0xda442d24U, newV1);
    helper.state_i = (helper.state_i + 15) & 0x0000000fU;

    return static_cast<float>(helper.STATE[helper.state_i] * FACT);
}

} /* namespace random */
} /* namespace tgon */