/**
 * filename TRandom.h
 * author   ggomdyu
 * since    03/14/2016
 */

#pragma once
#include "../Platform/TConfig.h"

namespace tgon
{

class TGON_API Random
{
/**
 * @section Public methods
 */
public:
    /* @return	Return random value between min~max as int */
    static int Range(int min, int max);

    /* @return	Return random value between min~max as float */
    static float Range(float min, float max);

/**
 * @section Private methods
 */
private:
	/**
	 * @brief   Random number generator which faster than the mersenne-Twister above 40%
	 * @see     http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	 * @return  Return random value between 0.0 ~ 1.0
	 */
    static float WELLRNG512a();

/**
 * @section Ctor/Dtor
 */
private:
    Random() = delete;
};

} /* namespace tgon */