/**
 * @file    TimeModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include "Module.h"

namespace tgon
{

class TimeModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(TimeModule)

/**@section Constructor */
public:
    TimeModule();

/**@section Method */
public:
    void SetTimeScale(float timeScale) noexcept;
    float GetTimeScale() const noexcept;
    float GetTickTime() const noexcept;
    void Update() override;

/**@section Variable */
private:
    int64_t m_lastRecordedTickTime;
    float m_timeScale;
    float m_tickTime;
};

} /* namespace tgon */
