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

class AudioPlayer final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioPlayer)

/**@section Constructor */
private:
    AudioPlayer(ALuint alSource, const std::shared_ptr<class AudioBuffer>& audioBuffer) noexcept;
    AudioPlayer(ALuint alSource, std::shared_ptr<class AudioBuffer>&& audioBuffer) noexcept;

public:
    AudioPlayer(AudioPlayer&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioPlayer();

/**@section Destructor */
public:
    AudioPlayer& operator=(AudioPlayer&& rhs) noexcept;

/**@section Method */
public:
    static std::optional<AudioPlayer> Create(const std::shared_ptr<class AudioBuffer>& audioBuffer);
    void Play();
    void Play(float volume, bool isLooping);
    bool IsPlaying() const;
    void Stop();
    void Pause();
    void Resume();
    void SetVolume(float volume);
    void SetPosition(float x, float y, float z);
    void SetVelocity(float x, float y, float z);
    static void SetListenerPosition(float x, float y, float z);
    static void SetListenerVelocity(float x, float y, float z);
    float GetVolume() const;
    void SetProgressInSeconds(float seconds);
    float GetProgressInSeconds() const;
    float GetTotalProgressInSeconds() const;
    void SetPitch(float pitch);
    float GetPitch() const;
    void SetLooping(bool isLooping);
    bool IsLooping() const;

private:
    static std::optional<ALuint> CreateALSource();
   
/**@section Variable */
private:
    ALuint m_alSource;
    std::shared_ptr<class AudioBuffer> m_audioBuffer;
};

} /* namespace tgon */
