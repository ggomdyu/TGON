/**
 * @file    AudioPlayer.h
 * @author  ggomdyu
 * @since   05/06/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <optional>

#include "Core/RuntimeObject.h"

namespace tgon
{

class AudioClip;

class AudioSource final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioSource)

/**@section Constructor */
public:
    AudioSource(ALuint alSource) noexcept;
    AudioSource(AudioSource&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioSource() override;

/**@section Operator */
public:
    AudioSource& operator=(AudioSource&& rhs) noexcept;

/**@section Method */
public:
    static std::optional<AudioSource> Create();
    void Play();
    void Stop();
    void Pause();
    void UnPause();
    void SetClip(const std::shared_ptr<AudioClip>& audioBuffer);
    void SetClip(std::shared_ptr<AudioClip>&& audioBuffer);
    void SetVolume(float volume);
    void SetPosition(float x, float y, float z);
    void SetVelocity(float x, float y, float z);
    static void SetListenerPosition(float x, float y, float z);
    static void SetListenerVelocity(float x, float y, float z);
    void SetProgressInSeconds(float seconds);
    void SetPitch(float pitch);
    void SetLoop(bool isLoop);
    float GetVolume() const;
    float GetProgressInSeconds() const;
    float GetTotalProgressInSeconds() const;
    float GetPitch() const;
    std::shared_ptr<AudioClip> GetClip() noexcept;
    std::shared_ptr<const AudioClip> GetClip() const noexcept;
    bool IsLoop() const;
    bool IsPlaying() const;

private:
    static std::optional<ALuint> CreateALSource();
   
/**@section Variable */
private:
    ALuint m_alSource;
    std::shared_ptr<AudioClip> m_audioClip;
};

} /* namespace tgon */
