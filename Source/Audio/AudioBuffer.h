/**
 * @file    AudioBuffer.h
 * @author  ggomdyu
 * @since   04/30/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <memory>
#include <gsl/span>

#if TGON_PLATFORM_MACOS
#   include <OpenAL/al.h>
#else
#   include <AL/al.h>
#endif

#include "Core/NonCopyable.h"

namespace tgon
{

enum class AudioFormat
{
    Unknown,
    Wav,
    Vorbis,
    Mp3,
    Flac,
    M4a,
    Opus,
};

class AudioBuffer :
    private NonCopyable
{
/**@section Constructor */
public:
    AudioBuffer();
    explicit AudioBuffer(const char* filePath);
    explicit AudioBuffer(const gsl::span<const std::byte>& fileData);
    AudioBuffer(AudioBuffer&& rhs) noexcept;

/**@section Operator */
public:
    AudioBuffer& operator=(AudioBuffer&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioBuffer();

/**@section Method */
public:
    bool Initialize(const char* filePath);
    bool Initialize(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat);
    bool Initialize(const gsl::span<const std::byte>& fileData);
    const std::byte* GetAudioData() const noexcept;
    int32_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;
    ALenum GetALFormat() const noexcept;
    ALuint GetALBufferId() const noexcept;

private:
    bool Decode(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat);
    void Destroy();

/**@section Variable */
private:
    ALuint m_alBufferId = 0;
    std::unique_ptr<std::byte[]> m_audioData;
    int32_t m_audioDataBytes = 0;
    int32_t m_bitsPerSample = 0;
    int32_t m_channels = 0;
    int32_t m_samplingRate = 0;
    ALenum m_alFormat = 0;
};

} /* namespace tgon */
