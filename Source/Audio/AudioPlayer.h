/**
 * @file    AudioPlayer.h
 * @author  ggomdyu
 * @since   05/06/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <optional>

#include "Core/RuntimeObject.h"

#include "AudioBuffer.h"

namespace tgon
{

class AudioPlayer final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioPlayer)

/**@section Constructor */
public:
    AudioPlayer(ALuint alSource) noexcept;
    AudioPlayer(AudioPlayer&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioPlayer() override;

/**@section Destructor */
public:
    AudioPlayer& operator=(AudioPlayer&& rhs) noexcept;

/**@section Method */
public:
    static std::optional<AudioPlayer> Create();
    void Play();
    void Play(float volume, bool isLooping);
    bool IsPlaying() const;
    void Stop();
    void Pause();
    void Resume();
    void SetAudioBuffer(const std::shared_ptr<AudioBuffer>& audioBuffer);
    void SetAudioBuffer(std::shared_ptr<AudioBuffer>&& audioBuffer);
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
