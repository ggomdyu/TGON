/**
 * @file    AudioPlayer.h
 * @author  ggomdyu
 * @since   05/06/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include "Core/NonCopyable.h"
#include "Math/Vector3.h"

#include "AudioBuffer.h"

namespace tgon
{

class TGON_API AudioPlayer final :
    private NonCopyable
{
/**@section Constructor */
public:
    AudioPlayer();
    AudioPlayer(AudioPlayer&& rhs) noexcept;
    explicit AudioPlayer(const std::shared_ptr<AudioBuffer>& audioBuffer);

/**@section Destructor */
public:
    ~AudioPlayer();

/**@section Destructor */
public:
    AudioPlayer& operator=(AudioPlayer&& rhs) noexcept;

/**@section Method */
public:
    void Initialize(const std::shared_ptr<AudioBuffer>& audioBuffer);
    void Play();
    void Play(float volume, bool isLooping);
    bool IsPlaying() const;
    void Stop();
    void Pause();
    void Resume();
    void SetVolume(float volume);
    void SetPosition(const Vector3& position);
    void SetVelocity(const Vector3& velocity);
    static void SetListenerPosition(const Vector3& position);
    static void SetListenerVelocity(const Vector3& velocity);
    float GetVolume() const;
    void SetProgressInSeconds(float seconds);
    float GetProgressInSeconds() const;
    float GetTotalProgressInSeconds() const;
    void SetPitch(float pitch);
    float GetPitch() const;
    void SetLooping(bool isLooping);
    bool IsLooping() const;

private:
    static ALuint CreateALSourceHandle();
    void Destroy();

/**@section Variable */
private:
    ALuint m_alSource;
    std::shared_ptr<AudioBuffer> m_audioBuffer;
};

class StreamAudioPlayer
{
public:
};

} /* namespace tgon */
