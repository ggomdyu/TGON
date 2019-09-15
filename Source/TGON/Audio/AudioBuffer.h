/**
 * @file    AudioBuffer.h
 * @author  ggomdyu
 * @since   04/30/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <cstdint>
#include <memory>
#include <string>

#include "Platform/Config.h"
#if TGON_PLATFORM_MACOS
#   include <OpenAL/al.h>
#else
#   include <al.h>
#endif

#include "Core/NonCopyable.h"

namespace tgon
{

enum class AudioFormat
{
    Unknown,
    Wav,
    OggVorbis,
    Mp3,
    Flac,
    M4a,
    Opus,
};

enum class AudioSampleFormat
{
    Mono8 = AL_FORMAT_MONO8,
    Mono16 = AL_FORMAT_MONO16,
    Stereo8 = AL_FORMAT_STEREO8,
    Stereo16 = AL_FORMAT_STEREO16,
};

class TGON_API AudioBuffer : NonCopyable
{
/**@section Constructor */
public:
    AudioBuffer();
    explicit AudioBuffer(const std::string& filePath);
    AudioBuffer(const std::byte* fileData, std::size_t fileDataBytes);
    AudioBuffer(AudioBuffer&& rhs) = default;

/**@section Operator */
public:
    AudioBuffer& operator=(AudioBuffer&& rhs) = default;

/**@section Destructor */
public:
    ~AudioBuffer();

/**@section Method */
public:
    bool SetAudioData(const std::string& filePath);
    bool SetAudioData(const std::byte* fileData, std::size_t fileDataBytes, AudioFormat audioFormat);
    bool SetAudioData(const std::byte* fileData, std::size_t fileDataBytes);
    bool IsValid() const noexcept;
    const std::byte* GetAudioData() const noexcept;
    size_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;
    ALenum GetALFormat() const noexcept;
    ALuint GetALBufferId() const noexcept;
    const std::string& GetFilePath() const noexcept;

private:
    bool Decode(const std::byte* fileData, std::size_t fileDataBytes, AudioFormat audioFormat);

/**@section Variable */
private:
    std::string m_filePath;
    std::unique_ptr<std::byte[]> m_audioData;
    ALuint m_alBufferId;
    size_t m_audioDataBytes;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
    ALenum m_alFormat;
};

} /* namespace tgon */
