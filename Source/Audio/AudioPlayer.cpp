#include "PrecompiledHeader.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <AL/alc.h>
#endif

#include "AudioPlayer.h"
#include "OpenALDebug.h"

namespace tgon
{

AudioPlayer::AudioPlayer(ALuint alSource) noexcept :
    m_alSource(alSource)
{
}

AudioPlayer::AudioPlayer(AudioPlayer&& rhs) noexcept :
    m_alSource(rhs.m_alSource),
    m_audioBuffer(std::move(rhs.m_audioBuffer))
{
    rhs.m_alSource = 0;
}

AudioPlayer::~AudioPlayer()
{
    if (m_alSource != 0)
    {
        this->Stop();
        TGON_AL_ERROR_CHECK(alDeleteSources(1, &m_alSource))
    }
}

AudioPlayer& AudioPlayer::operator=(AudioPlayer&& rhs) noexcept
{
    std::swap(m_alSource, rhs.m_alSource);
    std::swap(m_audioBuffer, rhs.m_audioBuffer);

    return *this;
}

std::optional<AudioPlayer> AudioPlayer::Create()
{
    auto alSource = CreateALSource();
    if (alSource.has_value() == false)
    {
        return {};
    }

    return AudioPlayer(*alSource);
}

void AudioPlayer::Play()
{
    this->SetProgressInSeconds(0.0f);
    TGON_AL_ERROR_CHECK(alSourcePlay(m_alSource))
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
    TGON_AL_ERROR_CHECK(alGetSourcei(m_alSource, AL_SOURCE_STATE, &isPlaying))

    return isPlaying == AL_PLAYING;
}

void AudioPlayer::Stop()
{
    TGON_AL_ERROR_CHECK(alSourceStop(m_alSource))
}

void AudioPlayer::Pause()
{
    TGON_AL_ERROR_CHECK(alSourcePause(m_alSource))
}

void AudioPlayer::Resume()
{
    TGON_AL_ERROR_CHECK(alSourcePlay(m_alSource))
}

void AudioPlayer::SetAudioBuffer(const std::shared_ptr<AudioBuffer>& audioBuffer)
{
    TGON_AL_ERROR_CHECK(alSourcei(m_alSource, AL_BUFFER, audioBuffer->GetNativeBuffer()));
    m_audioBuffer = audioBuffer;
}

void AudioPlayer::SetAudioBuffer(std::shared_ptr<AudioBuffer>&& audioBuffer)
{
    TGON_AL_ERROR_CHECK(alSourcei(m_alSource, AL_BUFFER, audioBuffer->GetNativeBuffer()));
    m_audioBuffer = std::move(audioBuffer);
}

void AudioPlayer::SetVolume(float volume)
{
    TGON_AL_ERROR_CHECK(alSourcef(m_alSource, AL_GAIN, volume))
}

void AudioPlayer::SetPosition(float x, float y, float z)
{
    TGON_AL_ERROR_CHECK(alSource3f(m_alSource, AL_POSITION, x, y, z))
}

void AudioPlayer::SetVelocity(float x, float y, float z)
{
    TGON_AL_ERROR_CHECK(alSource3f(m_alSource, AL_VELOCITY, x, y, z))
}

void AudioPlayer::SetListenerPosition(float x, float y, float z)
{
    TGON_AL_ERROR_CHECK(alListener3f(AL_POSITION, x, y, z))
}

void AudioPlayer::SetListenerVelocity(float x, float y, float z)
{
    TGON_AL_ERROR_CHECK(alListener3f(AL_VELOCITY, x, y, z))
}

float AudioPlayer::GetVolume() const
{
    float volume = 0.0f;
    TGON_AL_ERROR_CHECK(alGetSourcef(m_alSource, AL_GAIN, &volume))

    return volume;
}

void AudioPlayer::SetProgressInSeconds(float seconds)
{
    TGON_AL_ERROR_CHECK(alSourcef(m_alSource, AL_SEC_OFFSET, seconds))
}

float AudioPlayer::GetProgressInSeconds() const
{
    float seconds = 0;
    TGON_AL_ERROR_CHECK(alGetSourcef(m_alSource, AL_SEC_OFFSET, &seconds))

    return seconds;
}

float AudioPlayer::GetTotalProgressInSeconds() const
{
    if (m_audioBuffer == nullptr)
    {
        return 0.0f;
    }
    
    return static_cast<float>(m_audioBuffer->GetAudioData().size()) / (m_audioBuffer->GetSamplingRate() * m_audioBuffer->GetChannels() * (static_cast<float>(m_audioBuffer->GetBitsPerSample()) * 0.125f));
}

void AudioPlayer::SetPitch(float pitch)
{
    TGON_AL_ERROR_CHECK(alSourcef(m_alSource, AL_PITCH, pitch))
}

float AudioPlayer::GetPitch() const
{
    float pitch = 0.0f;
    TGON_AL_ERROR_CHECK(alGetSourcef(m_alSource, AL_PITCH, &pitch))

    return pitch;
}

void AudioPlayer::SetLooping(bool isLooping)
{
    TGON_AL_ERROR_CHECK(alSourcei(m_alSource, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE))
}

bool AudioPlayer::IsLooping() const
{
    ALint isLooping = AL_FALSE;
    TGON_AL_ERROR_CHECK(alGetSourcei(m_alSource, AL_LOOPING, &isLooping))

    return isLooping == AL_TRUE ? true : false;
}

std::optional<ALuint> AudioPlayer::CreateALSource()
{
    ALuint alSource;
    TGON_AL_ERROR_CHECK(alGenSources(1, &alSource));
    if (alGetError() != AL_NO_ERROR)
    {
        return {};
    }

    return alSource;
}

} /* namespace tgon */
