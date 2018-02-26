/**
 * @filename    IModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "IModule.h"

namespace tgon
{
namespace game
{

class TGON_API TimeModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(TimeModule)

/* @section Public constructor */
public:
    TimeModule();
    virtual ~TimeModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;

    void SetTimeScale(float timeScale);
    float GetTimeScale() const;
    float GetDeltaTime() const;

/* @section Private variable */
private:
    uint64_t m_prevTime;

    float m_timeScale;
    float m_deltaTime;
};

} /* namespace game */
} /* namespace tgon */
