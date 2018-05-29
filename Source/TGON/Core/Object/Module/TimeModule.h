/**
 * @filename    TimeModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "IModule.h"

namespace tgon
{

class TGON_API TimeModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(TimeModule)

/* @section Public constructor */
public:
    TimeModule();

/* @section Public destructor */
public:
    virtual ~TimeModule() override = default;

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
