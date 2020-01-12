#include "PrecompiledHeader.h"

#include "Importer/WavAudioImporter.h"
#include "Importer/VorbisAudioImporter.h"
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

AudioBuffer::AudioBuffer()
{
    TGON_AL_ERROR_CHECK(alGenBuffers(1, &m_alBufferId));
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

AudioBuffer::AudioBuffer(AudioBuffer&& rhs) noexcept :
    m_alBufferId(rhs.m_alBufferId),
    m_audioData(std::move(rhs.m_audioData)),
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

AudioBuffer& AudioBuffer::operator=(AudioBuffer&& rhs) noexcept
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
    if (this->Decode(fileData, audioFormat) == false)
    {
        return false;
    }

    m_alFormat = ConvertToALFormat(m_channels, m_bitsPerSample);
    if (m_alFormat == -1)
    {
        return false;
    }
        
    TGON_AL_ERROR_CHECK(alBufferData(m_alBufferId, m_alFormat, m_audioData.get(), static_cast<ALsizei>(m_audioDataBytes), m_samplingRate));

    return true;
}

bool AudioBuffer::Initialize(const gsl::span<const std::byte>& fileData)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioImporter::IsExactFormat(fileData))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (VorbisAudioImporter::IsExactFormat(fileData))
    {
        audioFormat = AudioFormat::Vorbis;
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

int32_t AudioBuffer::GetAudioDataBytes() const noexcept
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

bool AudioBuffer::Decode(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat)
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
        
    case AudioFormat::Vorbis:
        {
            VorbisAudioImporter importer;
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
        TGON_AL_ERROR_CHECK(alDeleteBuffers(1, &m_alBufferId));
        m_alBufferId = 0;
    }
}

} /* namespace tgon */
