#include "PrecompiledHeader.h"

#if TGON_PLATFORM_MACOS
#   include <OpenAL/alc.h>
#else
#   include <alc.h>
#endif

#include "Platform/Config.h"

#include "Importer/WavAudioImporter.h"
#include "Importer/OggVorbisAudioImporter.h"

#include "AudioBuffer.h"
#include "AudioBufferUtility.h"

namespace tgon
{

AudioBuffer::AudioBuffer() noexcept :
    m_audioDataBytes(0),
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0),
    m_alBufferId(0),
    m_alFormat(0)
{
}

AudioBuffer::AudioBuffer(const std::string& filePath) :
    AudioBuffer()
{
    this->Initialize(filePath);
}

AudioBuffer::AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes) :
    AudioBuffer()
{
    this->Initialize(filePath, srcData, srcDataBytes);
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_alBufferId);
}

bool AudioBuffer::Initialize(const std::string& filePath)
{
#ifdef _MSC_VER
    FILE* file = nullptr;
    fopen_s(&file, filePath.c_str(), "rb");
#else
    FILE* file = fopen(filePath.c_str(), "rb");
#endif
    if (file == nullptr)
    {
        return false;
    }

    // Read the audio data from the file.
    std::vector<uint8_t> audioData;
    {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        audioData.resize(fileSize + 1);
        fread(audioData.data(), 1, fileSize, file);
    };
    fclose(file);

    size_t extensionOffset = filePath.rfind('.') + 1;
    return this->Initialize(filePath, audioData.data(), audioData.size(), ConvertStringToAudioFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset));
}

bool AudioBuffer::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat)
{
    if (this->ParseData(srcData, srcDataBytes, audioFormat) == false)
    {
        return false;
    }

    m_alFormat = ConvertToALFormat(m_channels, m_bitsPerSample);
    if (m_alFormat == 0)
    {
        return false;
    }

    if (this->InitializeALBuffer(m_audioData.get(), static_cast<ALsizei>(m_audioDataBytes), m_alFormat, m_samplingRate) == false)
    {
        return false;
    }

    return true;
}

bool AudioBuffer::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioImporter::VerifyFormat(srcData, srcDataBytes))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (OggVorbisAudioImporter::VerifyFormat(srcData, srcDataBytes))
    {
        audioFormat = AudioFormat::OggVorbis;
    }
    else
    {
        return false;
    }

    return this->Initialize(filePath, srcData, srcDataBytes, audioFormat);
}

bool AudioBuffer::IsValid() const noexcept
{
    return m_audioData != nullptr;
}

const std::string& AudioBuffer::GetFilePath() const noexcept
{
    return m_filePath;
}

const uint8_t* AudioBuffer::GetAudioData() const noexcept
{
    return m_audioData.get();
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

bool AudioBuffer::ParseData(const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat)
{
    switch (audioFormat)
    {
    case AudioFormat::Wav:
        {
            WavAudioImporter importer(srcData, srcDataBytes);
            if (importer.IsValid())
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
            OggVorbisAudioImporter importer(srcData, srcDataBytes);
            if (importer.IsValid())
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

bool AudioBuffer::InitializeALBuffer(const uint8_t* audioData, ALsizei audioDataBytes, ALenum alFormat, int32_t samplingRate)
{
    if (m_alBufferId == 0)
    {
        alGenBuffers(1, &m_alBufferId);
        if (alGetError() != AL_NO_ERROR)
        {
            return false;
        }
    }

    alBufferData(m_alBufferId, alFormat, audioData, audioDataBytes, samplingRate);
    if (alGetError() != AL_NO_ERROR)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
