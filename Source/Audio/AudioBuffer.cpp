#include "PrecompiledHeader.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/al.h>
#else
#   include <AL/al.h>
#endif

#include "Importer/WavAudioDecoder.h"
#include "Importer/VorbisAudioDecoder.h"
#include "IO/File.h"

#include "AudioBuffer.h"
#include "OpenALDebug.h"

namespace tgon
{

inline ALenum ConvertToALFormat(int32_t channels, int32_t bitsPerSample)
{
    if (channels == 1)
    {
        if (bitsPerSample == 8)
        {
            return AL_FORMAT_MONO8;
        }
        else if (bitsPerSample == 16)
        {
            return AL_FORMAT_MONO16;
        }
    }
    else if (channels == 2)
    {
        if (bitsPerSample == 8)
        {
            return AL_FORMAT_STEREO8;
        }
        else if (bitsPerSample == 16)
        {
            return AL_FORMAT_STEREO16;
        }
    }
    else if (channels == 4)
    {
        return alGetEnumValue("AL_FORMAT_QUAD16");
    }
    else if (channels == 6)
    {
        return alGetEnumValue("AL_FORMAT_51CHN16");
    }
    
    return 0;
}

AudioBuffer::AudioBuffer(AudioBuffer&& rhs) noexcept :
    m_alBufferId(rhs.m_alBufferId),
    m_audioData(std::move(rhs.m_audioData)),
    m_audioDataBytes(rhs.m_audioDataBytes),
    m_bitsPerSample(rhs.m_bitsPerSample),
    m_channels(rhs.m_channels),
    m_samplingRate(rhs.m_samplingRate)
{
    rhs.m_alBufferId = 0;
}

AudioBuffer::~AudioBuffer()
{
    if (m_alBufferId != 0)
    {
        TGON_AL_ERROR_CHECK(alDeleteBuffers(1, &m_alBufferId));
        m_alBufferId = 0;
    }
}

AudioBuffer& AudioBuffer::operator=(AudioBuffer&& rhs) noexcept
{
    std::swap(m_audioData, rhs.m_audioData);
    
    m_alBufferId = rhs.m_alBufferId;
    m_audioDataBytes = rhs.m_audioDataBytes;
    m_bitsPerSample = rhs.m_bitsPerSample;
    m_channels = rhs.m_channels;
    m_samplingRate = rhs.m_samplingRate;
    
    rhs.m_alBufferId = 0;
    
    return *this;
}

std::optional<AudioBuffer> AudioBuffer::Create(const char* filePath)
{
    auto fileData = File::ReadAllBytes(filePath, ReturnVectorTag{});
    if (fileData.has_value() == false)
    {
        return {};
    }

    return Create(*fileData);
}

std::optional<AudioBuffer> AudioBuffer::Create(const gsl::span<const std::byte>& fileData)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioDecoder::IsWav(fileData))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (VorbisAudioDecoder::IsVorbis(fileData))
    {
        audioFormat = AudioFormat::Vorbis;
    }
    else
    {
        return {};
    }

    return Create(fileData, audioFormat);
}

std::optional<AudioBuffer> AudioBuffer::Create(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat)
{
    std::shared_ptr<std::byte[]> audioData;
    int32_t audioDataBytes = 0;
    int32_t bitsPerSample = 0;
    int32_t channels = 0;
    int32_t samplingRate = 0;

    auto getDecodedAudioData = [&](auto& audioDecoder)
    {
        if (audioDecoder.has_value() == false)
        {
            return false;
        }

        audioData = audioDecoder->GetAudioData();
        audioDataBytes = audioDecoder->GetAudioDataBytes();
        bitsPerSample = audioDecoder->GetBitsPerSample();
        channels = audioDecoder->GetChannels();
        samplingRate = audioDecoder->GetSamplingRate();

        return true;
    };

    if (audioFormat == AudioFormat::Wav)
    {
        auto audioDecoder = WavAudioDecoder::Create(fileData);
        if (getDecodedAudioData(audioDecoder) == false)
        {
            return {};
        }
    }
    else if (audioFormat == AudioFormat::Vorbis)
    {
        auto audioDecoder = VorbisAudioDecoder::Create(fileData);
        if (getDecodedAudioData(audioDecoder) == false)
        {
            return {};
        }
    }

    return AudioBuffer(std::move(audioData), audioDataBytes, bitsPerSample, channels, samplingRate);
}

gsl::span<std::byte> AudioBuffer::GetAudioData() noexcept
{
    return {m_audioData.get(), static_cast<size_t>(m_audioDataBytes)};
}

gsl::span<const std::byte> AudioBuffer::GetAudioData() const noexcept
{
    return const_cast<AudioBuffer*>(this)->GetAudioData();
}

int32_t AudioBuffer::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

int32_t AudioBuffer::GetChannels() const noexcept
{
    return m_channels;
}

int32_t AudioBuffer::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

ALuint AudioBuffer::GetNativeBuffer() const noexcept
{
    return m_alBufferId;
}

ALuint AudioBuffer::CreateALBuffer()
{
    ALuint alBufferId = 0;
    TGON_AL_ERROR_CHECK(alGenBuffers(1, &alBufferId));

    return alBufferId;
}

} /* namespace tgon */
