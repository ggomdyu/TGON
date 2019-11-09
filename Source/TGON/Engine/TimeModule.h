/**
 * @file    TimeModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include "Module.h"

namespace tgon
{

class TGON_API TimeModule final :
	public Module
{
public:
    TGON_DECLARE_RTTI(TimeModule)

/**@section Constructor */
public:
    TimeModule();

/**@section Destructor */
public:
    virtual ~TimeModule() override = default;

/**@section Method */
public:
    virtual void Update() override;
    
    /**
     * @brief   Sets the scale which the time passing.
     * @param [in] timeScale    The scale of time passing.
     */
    void SetTimeScale(float timeScale) noexcept;
    
    /**
     * @brief   Gets the scale which the time passing.
     * @return  The scale of time passing.
     */
    float GetTimeScale() const noexcept;
    
    /**
     * @brief   Gets the elapsed time per frame.
     * @return  The elapsed time per frame.
     */
    float GetTickTime() const noexcept;

/**@section Variable */
private:
    uint64_t m_lastRecordedTickTime;
    float m_timeScale;
    float m_tickTime;
};

} /* namespace tgon */
