/**
 * author   ggomdyu
 * since    07/24/2016


 */

#pragma once
#include "Interface/IModule.h"

namespace tgon
{

class TGON_API TimeModule :
	public IModule
{
public:
    TGON_MAKE_OBJECT_INTERFACE(TimeModule)

/**
 * @section Ctor/Dtor
 */
public:
    TimeModule();
    virtual ~TimeModule() = default;

/**
 * @section Public methods
 */
public:
    virtual void Update();

/**
 * @section Gets
 */
    float GetElapsedTime() const;

/**
 * @section Private variables
 */
private:
    uint32_t m_oldTime;
    float m_elapsedTime;
};

} /* namespace tgon */
