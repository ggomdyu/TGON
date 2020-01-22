/**
 * @file    AudioBuffer.h
 * @author  ggomdyu
 * @since   04/30/2018
 * @see     https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
 */

#pragma once
#include <gsl/span>
#include <memory>
#include <optional>

#include "Core/RuntimeObject.h"

typedef unsigned int ALuint;

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

class AudioBuffer final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioBuffer)
    
/**@section Constructor */
public:
    AudioBuffer(const std::shared_ptr<std::byte>& audioData, int32_t audioDataBytes, int32_t bitsPerSample, int32_t channels, int32_t samplingRate) noexcept;
    AudioBuffer(AudioBuffer&& rhs) noexcept;
    
/**@section Operator */
public:
    AudioBuffer& operator=(AudioBuffer&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioBuffer() override;

/**@section Method */
public:
    static std::shared_ptr<AudioBuffer> Create(const char* filePath);
    static std::shared_ptr<AudioBuffer> Create(const gsl::span<const std::byte>& fileData);
    static std::shared_ptr<AudioBuffer> Create(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat);
    gsl::span<std::byte> GetAudioData() noexcept;
    gsl::span<const std::byte> GetAudioData() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;
    ALuint GetNativeBuffer() const noexcept;
   
private:
    static ALuint CreateALBuffer();

/**@section Variable */
protected:
    ALuint m_alBufferId = 0;
    std::shared_ptr<std::byte> m_audioData;
    int32_t m_audioDataBytes = 0;
    int32_t m_bitsPerSample = 0;
    int32_t m_channels = 0;
    int32_t m_samplingRate = 0;
};

} /* namespace tgon */
