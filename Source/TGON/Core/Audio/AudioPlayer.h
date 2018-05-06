/**
 * @filename    AudioPlayer.h
 * @author      ggomdyu
 * @since       05/06/2018
 * @see         https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include "Core/Math/Vector3.h"

#include "AudioBuffer.h"

namespace tgon
{

class AudioPlayer
{
/* @section Public constructor */
public:
    AudioPlayer();
    AudioPlayer(const std::shared_ptr<AudioBuffer>& audioBuffer);

public:
    ~AudioPlayer();

/* @section Public method */
public:
    void SetAudioBuffer(const std::shared_ptr<AudioBuffer>& audioBuffer);
    void Play(float volume, bool isLooping);
    bool IsPlaying() const;
    void Stop();
    void Pause();
    void Resume();
    void SetVolume(float volume);
    void SetPosition(const Vector3& position);
    static void SetListenerPosition(const Vector3& position);
    static void SetListenerVelocity(const Vector3& velocity);
    float GetVolume() const;
    float GetProgress() const;
    void SetPitch(float pitch);
    float GetPitch() const;
    void SetLooping(bool isLooping);
    bool IsLooping() const;

/* @section Private method */
private:
    ALuint CreateALSource() const;

/* @section Private variable */
private:
    std::shared_ptr<AudioBuffer> m_audioBuffer;
    ALuint m_alSource;
};

} /* namespace tgon */