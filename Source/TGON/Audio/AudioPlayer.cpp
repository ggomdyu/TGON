#include "PrecompiledHeader.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <alc.h>
#endif

#include "AudioPlayer.h"

namespace tgon
{

AudioPlayer::AudioPlayer() :
    m_alSource(0)
{
}

AudioPlayer::AudioPlayer(const std::shared_ptr<AudioBuffer>& audioBuffer) :
    AudioPlayer()
{
    this->Initialize(audioBuffer);
}

AudioPlayer::AudioPlayer(AudioPlayer&& rhs) noexcept :
    m_alSource(rhs.m_alSource),
    m_audioBuffer(std::move(rhs.m_audioBuffer))
{
    rhs.m_alSource = 0;
}

AudioPlayer::~AudioPlayer()
{
    this->Destroy();
}

AudioPlayer& AudioPlayer::operator=(AudioPlayer&& rhs) noexcept
{
    this->Destroy();

    m_alSource = rhs.m_alSource;
    m_audioBuffer = std::move(rhs.m_audioBuffer);

    rhs.m_alSource = 0;
    rhs.m_audioBuffer = nullptr;
    
    return *this;
}

void AudioPlayer::Initialize(const std::shared_ptr<AudioBuffer>& audioBuffer)
{
    if (m_audioBuffer != nullptr)
    {
        this->Stop();
    }
    else if (m_alSource == 0)
    {
        m_alSource = this->CreateALSourceHandle();
    }

    m_audioBuffer = audioBuffer;

    alSourcei(m_alSource, AL_BUFFER, m_audioBuffer->GetALBufferId());
}

void AudioPlayer::Play()
{
    this->SetProgressInSeconds(0.0f);
    alSourcePlay(m_alSource);
}

void AudioPlayer::Play(float volume, bool isLooping)
{
    this->SetVolume(volume);
    this->SetLooping(isLooping);
    this->Play();
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
    float volume = 0.0f;
    alGetSourcef(m_alSource, AL_GAIN, &volume);

    return volume;
}

void AudioPlayer::SetProgressInSeconds(float seconds)
{
    alSourcef(m_alSource, AL_SEC_OFFSET, seconds);
}

float AudioPlayer::GetProgressInSeconds() const
{
    float seconds = 0;
    alGetSourcef(m_alSource, AL_SEC_OFFSET, &seconds);

    return seconds;
}

float AudioPlayer::GetTotalProgressInSeconds() const
{
    return static_cast<float>(m_audioBuffer->GetAudioDataBytes()) / (m_audioBuffer->GetSamplingRate() * m_audioBuffer->GetChannels() * (static_cast<float>(m_audioBuffer->GetBitsPerSample()) * 0.125f));
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

ALuint AudioPlayer::CreateALSourceHandle()
{
    ALuint alSource;
    alGenSources(1, &alSource);

    return alSource;
}

void AudioPlayer::Destroy()
{
    if (m_alSource != 0)
    {
        this->Stop();
        alDeleteSources(1, &m_alSource);
    }
}

} /* namespace tgon */
