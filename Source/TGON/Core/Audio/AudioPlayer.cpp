#include "PrecompiledHeader.pch"

#include <alc.h>

#include "AudioPlayer.h"

namespace tgon
{

AudioPlayer::AudioPlayer() :
    m_alSource(this->CreateALSource())
{
}

AudioPlayer::AudioPlayer(const std::shared_ptr<AudioBuffer>& audioBuffer) :
    m_alSource(this->CreateALSource())
{
    this->SetAudioBuffer(audioBuffer);
}

AudioPlayer::~AudioPlayer()
{
    this->Stop();
    alDeleteSources(1, &m_alSource);
}

void AudioPlayer::SetAudioBuffer(const std::shared_ptr<AudioBuffer>& audioBuffer)
{
    m_audioBuffer = audioBuffer;

    alSourcei(m_alSource, AL_BUFFER, m_audioBuffer->GetALBufferId());
}

void AudioPlayer::Play(float volume, bool isLooping)
{
    this->SetVolume(volume);
    this->SetLooping(isLooping);

    alSourcePlay(m_alSource);
}

bool AudioPlayer::IsPlaying() const
{
    ALint isPlaying = 0;
    alGetSourcei(m_alSource, AL_SOURCE_STATE, &isPlaying);

    return isPlaying == AL_PLAYING;
}

void AudioPlayer::Stop()
{
    alSourceStop(m_alSource);
}

void AudioPlayer::Pause()
{
    alSourcePause(m_alSource);
}

void AudioPlayer::Resume()
{
    alSourcePlay(m_alSource);
}

void AudioPlayer::SetVolume(float volume)
{
    alSourcef(m_alSource, AL_GAIN, volume);
}

void AudioPlayer::SetPosition(const Vector3& position)
{
    alSource3f(m_alSource, AL_POSITION, position.x, position.y, position.z);
}

void AudioPlayer::SetVelocity(const Vector3& velocity)
{
    alSource3f(m_alSource, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void AudioPlayer::SetListenerPosition(const Vector3& position)
{
    alListener3f(AL_POSITION, position.x, position.y, position.z);
}

void AudioPlayer::SetListenerVelocity(const Vector3& velocity)
{
    alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

float AudioPlayer::GetVolume() const
{
    return 0.0f;
}

float AudioPlayer::GetProgress() const
{
    return 0.0f;
}

void AudioPlayer::SetPitch(float pitch)
{
    alSourcef(m_alSource, AL_PITCH, pitch);
}

float AudioPlayer::GetPitch() const
{
    float pitch = 0.0f;
    alGetSourcef(m_alSource, AL_PITCH, &pitch);

    return pitch;
}

void AudioPlayer::SetLooping(bool isLooping)
{
    alSourcei(m_alSource, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);
}

bool AudioPlayer::IsLooping() const
{
    ALint isLooping = AL_FALSE;
    alGetSourcei(m_alSource, AL_LOOPING, &isLooping);

    return isLooping == AL_TRUE ? true : false;
}

ALuint AudioPlayer::CreateALSource() const
{
    ALuint alSource;
    alGenSources(1, &alSource);

    return alSource;
}

} /* namespace tgon */