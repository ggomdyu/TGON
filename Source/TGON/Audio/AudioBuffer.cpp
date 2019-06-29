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

AudioBuffer::AudioBuffer() :
    m_audioDataBytes(0),
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0),
    m_alBufferId(0),
    m_alFormat(0)
{
    alGenBuffers(1, &m_alBufferId);
    if (alGetError() != AL_NO_ERROR)
    {
        throw std::runtime_error("Failed to invoke alGenBuffers.");
    }
}

AudioBuffer::AudioBuffer(const std::string& filePath) :
    AudioBuffer()
{
    this->SetAudioData(filePath);
}

AudioBuffer::AudioBuffer(const uint8_t* fileData, std::size_t fileDataBytes) :
    AudioBuffer()
{
    this->SetAudioData(fileData, fileDataBytes);
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_alBufferId);
}

bool AudioBuffer::SetAudioData(const std::string& filePath)
{
    m_filePath = filePath;

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
    return this->SetAudioData(audioData.data(), audioData.size(), ConvertToAudioFormat(&filePath[0] + extensionOffset));
}

bool AudioBuffer::SetAudioData(const uint8_t* fileData, std::size_t fileDataBytes, AudioFormat audioFormat)
{
    if (this->Decode(fileData, fileDataBytes, audioFormat) == false)
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

bool AudioBuffer::SetAudioData(const uint8_t* fileData, std::size_t fileDataBytes)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioImporter::VerifyFormat(fileData, fileDataBytes))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (OggVorbisAudioImporter::VerifyFormat(fileData, fileDataBytes))
    {
        audioFormat = AudioFormat::OggVorbis;
    }
    else
    {
        return false;
    }

    return this->SetAudioData(fileData, fileDataBytes, audioFormat);
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

bool AudioBuffer::Decode(const uint8_t* fileData, std::size_t fileDataBytes, AudioFormat audioFormat)
{
    switch (audioFormat)
    {
    case AudioFormat::Wav:
        {
            WavAudioImporter importer(fileData, fileDataBytes);
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
            OggVorbisAudioImporter importer(fileData, fileDataBytes);
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

} /* namespace tgon */
