/**
 * @filename    TRandom.h
 * @author      ggomdyu
 * @since       03/14/2016
 */

#pragma once
#include "Core/Platform/TConfig.h"

namespace tgon {
namespace math {

class TGON_API Random
{
/**
 * @section Ctor/Dtor
 */
private:
    Random() = delete;
    ~Random() = delete;

/**
 * @section Public command method
 */
public:
    /* @return	Return random value between min~max as int */
    static int Range(int min, int max);

    /* @return	Return random value between min~max as float */
    static float Range(float min, float max);

/**
 * @section Private command method
 */
private:
	/**
	 * @brief   Random number generate algorithm that faster than the Mersenne Twister above 40%
	 * @see     http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	 * @return  Return random value between 0.0 ~ 1.0
	 */
    static float WELLRNG512a();
};

} /* namespace math */
} /* namespace tgon */