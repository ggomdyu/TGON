/**
 * @file    AudioPlayer.h
 * @author  ggomdyu
 * @since   05/06/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Math/Vector3.h"

#include "AudioBuffer.h"

namespace tgon
{

class AudioPlayer final :
    private boost::noncopyable
{
/**@section Public constructor */
public:
    AudioPlayer();
    AudioPlayer(AudioPlayer&& rhs);
    explicit AudioPlayer(const std::shared_ptr<AudioBuffer>& audioBuffer);

/**@section Public destructor */
public:
    ~AudioPlayer();

/**@section Public destructor */
public:
    AudioPlayer& operator=(AudioPlayer&& rhs);

/**@section Public method */
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

/**@section Private method */
private:
    ALuint CreateALSourceHandle() const;
    void Release();

/**@section Private variable */
private:
    std::shared_ptr<AudioBuffer> m_audioBuffer;
    ALuint m_alSource;
};

class StreamAudioPlayer
{
public:
};

} /* namespace tgon */
