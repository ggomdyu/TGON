#include "PrecompiledHeader.h"

#include <vector>

#include "Diagnostics/Debug.h"
#include "Text/StringTraits.h"
#include "Text/Hash.h"
#include "Importer/WavAudioImporter.h"
#include "Importer/OggVorbisAudioImporter.h"
#include "IO/File.h"

#include "AudioBuffer.h"

namespace tgon
{

inline AudioFormat ConvertToAudioFormat(const char* str)
{
    char lowercaseStr[32] {};
    BasicStringTraits<char>::ToLower(str, static_cast<int32_t>(strlen(str)), lowercaseStr);

    switch (X65599Hash(lowercaseStr))
    {
    case X65599Hash("wav"):
        return AudioFormat::Wav;
    case X65599Hash("ogg"):
        return AudioFormat::OggVorbis;
    case X65599Hash("mp3"):
        return AudioFormat::Mp3;
    case X65599Hash("flac"):
        return AudioFormat::Flac;
    case X65599Hash("m4a"):
        return AudioFormat::M4a;
    case X65599Hash("opus"):
        return AudioFormat::Opus;
    }

    return AudioFormat::Unknown;
}

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

AudioBuffer::AudioBuffer()
{
    alGenBuffers(1, &m_alBufferId);
    if (alGetError() != AL_NO_ERROR)
    {
        Debug::Fail("Failed to invoke alGenBuffers.");
    }
}

AudioBuffer::AudioBuffer(const char* filePath) :
    AudioBuffer()
{
    this->Initialize(filePath);
}

AudioBuffer::AudioBuffer(const gsl::span<const std::byte>& fileData) :
    AudioBuffer()
{
    this->Initialize(fileData);
}

AudioBuffer::AudioBuffer(AudioBuffer&& rhs) :
    m_audioData(std::move(rhs.m_audioData)),
    m_alBufferId(rhs.m_alBufferId),
    m_audioDataBytes(rhs.m_audioDataBytes),
    m_bitsPerSample(rhs.m_bitsPerSample),
    m_channels(rhs.m_channels),
    m_samplingRate(rhs.m_samplingRate),
    m_alFormat(rhs.m_alFormat)
{
    rhs.m_alBufferId = 0;
    rhs.m_audioDataBytes = 0;
    rhs.m_bitsPerSample = 0;
    rhs.m_channels = 0;
    rhs.m_samplingRate = 0;
    rhs.m_alFormat = 0;
}

AudioBuffer::~AudioBuffer()
{
    this->Destroy();
}

AudioBuffer& AudioBuffer::operator=(AudioBuffer&& rhs)
{
    this->Destroy();
    
    m_audioData = std::move(rhs.m_audioData);
    m_alBufferId = rhs.m_alBufferId;
    m_audioDataBytes = rhs.m_audioDataBytes;
    m_bitsPerSample = rhs.m_bitsPerSample;
    m_channels = rhs.m_channels;
    m_samplingRate = rhs.m_samplingRate;
    m_alFormat = rhs.m_alFormat;
    
    rhs.m_alBufferId = 0;
    rhs.m_audioDataBytes = 0;
    rhs.m_bitsPerSample = 0;
    rhs.m_channels = 0;
    rhs.m_samplingRate = 0;
    rhs.m_alFormat = 0;
    
    return *this;
}

bool AudioBuffer::Initialize(const char* filePath)
{
    auto fileData = File::ReadAllBytes(filePath, ReturnVectorTag{});
    if (fileData.has_value() == false)
    {
        return false;
    }

    return this->Initialize(*fileData);
}

bool AudioBuffer::Initialize(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat)
{
    if (this->DecodeFileData(fileData, audioFormat) == false)
    {
        return false;
    }

    m_alFormat = ConvertToALFormat(m_channels, m_bitsPerSample);
    if (m_alFormat == 0)
    {
        return false;
    }

    alBufferData(m_alBufferId, m_alFormat, m_audioData.get(), static_cast<ALsizei>(m_audioDataBytes), m_samplingRate);
    if (alGetError() != AL_NO_ERROR)
    {
        return false;
    }

    return true;
}

bool AudioBuffer::Initialize(const gsl::span<const std::byte>& fileData)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioImporter::IsExactFormat(fileData))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (OggVorbisAudioImporter::IsExactFormat(fileData))
    {
        audioFormat = AudioFormat::OggVorbis;
    }
    else
    {
        return false;
    }

    return this->Initialize(fileData, audioFormat);
}

const std::byte* AudioBuffer::GetAudioData() const noexcept
{
    return &m_audioData[0];
}

size_t AudioBuffer::GetAudioDataBytes() const noexcept
{
    return m_audioDataBytes;
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

ALenum AudioBuffer::GetALFormat() const noexcept
{
    return m_alFormat;
}

ALuint AudioBuffer::GetALBufferId() const noexcept
{
    return m_alBufferId;
}

bool AudioBuffer::DecodeFileData(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat)
{
    switch (audioFormat)
    {
    case AudioFormat::Wav:
        {
            WavAudioImporter importer;
            if (importer.Initialize(fileData))
            {
                m_audioData = std::move(importer.GetAudioData());
                m_audioDataBytes = importer.GetAudioDataBytes();
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();
                
                return true;
            }
        }
        break;
        
    case AudioFormat::OggVorbis:
        {
            OggVorbisAudioImporter importer;
            if (importer.Initialize(fileData))
            {
                m_audioData = std::move(importer.GetAudioData());
                m_audioDataBytes = importer.GetAudioDataBytes();
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();

                return true;
            }
        }
        break;

    case AudioFormat::Mp3:
    case AudioFormat::Flac:
    case AudioFormat::M4a:
    case AudioFormat::Opus:
    case AudioFormat::Unknown:
        break;
    }

    return false;
}

void AudioBuffer::Destroy()
{
    if (m_alBufferId != 0)
    {
        alDeleteBuffers(1, &m_alBufferId);
        m_alBufferId = 0;
    }
}

} /* namespace tgon */
