/**
 * @file    TimeModule.h
 * @author  ggomdyu
 * @since   ß07/24/2016
 */

#pragma once
#include "IModule.h"

namespace tgon
{

class TGON_API TimeModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(TimeModule);

/* @section Public constructor */
public:
    TimeModule();

/* @section Public destructor */
public:
    virtual ~TimeModule() override = default;

/* @section Public method */
public:
    virtual void Update() override;
    
    /**
     * @brief                   Sets the scale which the time passing.
     * @param [in] timeScale    The scale of time passing.
     */
    void SetTimeScale(float timeScale) noexcept;
    
    /**
     * @brief   Gets the scale which the time passing.
     * @return  The scale of time passing.
     */
    float GetTimeScale() const noexcept;
    
    /**
     * @brief   Gets the elapsed time per each frame.
     * @return  The elapsed time per each frame.
     */
    float GetTickTime() const noexcept;

/* @section Private variable */
private:
    uint64_t m_lastRecordedTickTime;
    float m_timeScale;
    float m_tickTime;
};

} /* namespace tgon */
