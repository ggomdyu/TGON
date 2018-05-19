#include "PrecompiledHeader.h"

#include <alc.h>

#include "Core/Utility/StaticInvoke.h"

#include "AudioBuffer.h"
#include "AudioBufferUtility.h"
#include "Importer/Wav/WavAudioImporter.h"
#include "Importer/OggVorbis/OggVorbisAudioImporter.h"

namespace tgon
{

AudioBuffer::AudioBuffer() :
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0),
    m_alBufferId(0),
    m_alFormat(0)
{
    TGON_STATIC_INVOKE([]()
    {
        ALCdevice* device = alcOpenDevice(nullptr);
        if (device == nullptr)
        {
            return;
        }

        ALCcontext* context = alcCreateContext(device, nullptr);
        if (context == nullptr)
        {
            return;
        }

        alcMakeContextCurrent(context);
    });
}

AudioBuffer::AudioBuffer(const std::string& filePath) :
    AudioBuffer()
{
    this->Initialize(filePath);
}

AudioBuffer::AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat) :
    AudioBuffer()
{
    this->Initialize(filePath, srcData, srcDataBytes, audioFormat);
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
    FILE* file = fopen(filePath.c_str(), "rb");
    if (file == nullptr)
    {
        return false;
    }

    // Read the audio data from file.
    std::vector<uint8_t> audioData;
    {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        audioData.resize(fileSize + 1);
        fread(audioData.data(), 1, fileSize, file);
    };
    fclose(file);

    std::size_t extensionOffset = filePath.rfind('.') + 1;
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

    if (this->InitializeALBuffer(m_audioData, m_alFormat, m_samplingRate) == false)
    {
        return false;
    }

    return true;
}

bool AudioBuffer::Initialize(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
{
    AudioFormat audioFormat = AudioFormat::Unknown;
    if (WavAudioImporter<>::VerifyFormat(srcData, srcDataBytes))
    {
        audioFormat = AudioFormat::Wav;
    }
    else if (OggVorbisAudioImporter<>::VerifyFormat(srcData, srcDataBytes))
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
    return m_audioData.size() > 0;
}

const std::string& AudioBuffer::GetFilePath() const noexcept
{
    return m_filePath;
}

const std::vector<uint8_t>& AudioBuffer::GetSoundData() const noexcept
{
    return m_audioData;
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
            WavAudioImporter<> importer(srcData, srcDataBytes);
            if (importer.IsValid())
            {
                m_audioData = std::move(importer.GetAudioData());
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();

                return true;
            }
        }
        break;

    case AudioFormat::OggVorbis:
        {
            OggVorbisAudioImporter<> importer(srcData, srcDataBytes);
            if (importer.IsValid())
            {
                m_audioData = std::move(importer.GetAudioData());
                m_bitsPerSample = importer.GetBitsPerSample();
                m_channels = importer.GetChannels();
                m_samplingRate = importer.GetSamplingRate();

                return true;
            }
        }
        break;
    }

    return false;
}

bool AudioBuffer::InitializeALBuffer(const std::vector<uint8_t>& audioData, ALenum alFormat, int32_t samplingRate)
{
    if (m_alBufferId == 0)
    {
        alGenBuffers(1, &m_alBufferId);
        if (alGetError() != AL_NO_ERROR)
        {
            return false;
        }
    }

    alBufferData(m_alBufferId, alFormat, audioData.data(), audioData.size(), samplingRate);
    if (alGetError() != AL_NO_ERROR)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */