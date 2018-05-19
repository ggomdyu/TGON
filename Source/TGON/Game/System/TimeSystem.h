/**
 * @filename    TimeSystem.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "ISystem.h"

namespace tgon
{

class TGON_API TimeSystem :
	public ISystem
{
/* @section Public constructor */
public:
    TimeSystem();

/* @section Public destructor */
public:
    virtual ~TimeSystem() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    void SetTimeScale(float timeScale);
    float GetTimeScale() const;
    float GetTickTime() const;

/* @section Private variable */
private:
    uint64_t m_prevTime;
    float m_timeScale;
    float m_tickTime;
};

} /* namespace tgon */