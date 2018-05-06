#include "PrecompiledHeader.pch"

#include <alc.h>

#include "Core/Utility/StaticInvoke.h"

#include "AudioBuffer.h"
#include "AudioBufferUtility.h"
#include "Importer/Wav/WavAudioImporter.h"
#include "Importer/OggVorbis/OggVorbisAudioImporter.h"
#include <functional>
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
    this->Import(filePath);
}

AudioBuffer::AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat) :
    AudioBuffer()
{
    this->Import(filePath, srcData, srcDataBytes, audioFormat);
}

AudioBuffer::AudioBuffer(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes) :
    AudioBuffer()
{
    this->Import(filePath, srcData, srcDataBytes);
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_alBufferId);
}

bool AudioBuffer::Import(const std::string& filePath)
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
    return this->Import(filePath, audioData.data(), audioData.size(), ConvertStringToAudioFormat(&filePath[0] + extensionOffset, filePath.size() - extensionOffset));
}

bool AudioBuffer::Import(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes, AudioFormat audioFormat)
{
    if (this->ParseData(srcData, srcDataBytes, audioFormat) == false)
    {
        return false;
    }

    m_alFormat = this->ConvertToALFormat(m_channels, m_bitsPerSample);
    if (m_alFormat == 0)
    {
        return false;
    }

    m_alBufferId = this->CreateALBuffer(*m_soundData, m_alFormat, m_samplingRate);
    if (m_alBufferId == -1)
    {
        return false;
    }

    return true;
}

bool AudioBuffer::Import(const std::string& filePath, const uint8_t* srcData, std::size_t srcDataBytes)
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

    return this->Import(filePath, srcData, srcDataBytes, audioFormat);
}

bool AudioBuffer::IsValid() const noexcept
{
    return m_soundData->size() > 0;
}

const std::string& AudioBuffer::GetFilePath() const noexcept
{
    return m_filePath;
}

const std::shared_ptr<std::vector<uint8_t>>& AudioBuffer::GetSoundData() const noexcept
{
    return m_soundData;
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
                m_soundData = std::make_shared<decltype(m_soundData)::element_type>(std::move(importer.GetSoundData()));
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
                m_soundData = std::make_shared<decltype(m_soundData)::element_type>(std::move(importer.GetSoundData()));
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

ALenum AudioBuffer::ConvertToALFormat(int32_t channels, int32_t bitsPerSample) const
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

ALuint AudioBuffer::CreateALBuffer(const std::vector<uint8_t>& soundData, ALenum alFormat, int32_t samplingRate) const
{
    ALuint alBuffer = 0;
    alGenBuffers(1, &alBuffer);
    if (alGetError() != AL_NO_ERROR)
    {
        return -1;
    }

    alBufferData(alBuffer, alFormat, soundData.data(), soundData.size(), samplingRate);
    
    return alBuffer;
}

} /* namespace tgon */