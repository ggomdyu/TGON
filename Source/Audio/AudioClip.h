#pragma once

#include <gsl/span>
#include <memory>
#include <optional>

#include "Core/RuntimeObject.h"

typedef unsigned int ALuint;

namespace tg
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

class AudioClip final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(AudioClip)
    
/**@section Constructor */
public:
    AudioClip(const std::shared_ptr<std::byte>& audioData, int32_t audioDataBytes, int32_t bitsPerSample, int32_t channels, int32_t samplingRate) noexcept;
    AudioClip(AudioClip&& rhs) noexcept;
    
/**@section Operator */
public:
    AudioClip& operator=(AudioClip&& rhs) noexcept;

/**@section Destructor */
public:
    ~AudioClip() override;

/**@section Method */
public:
    static std::shared_ptr<AudioClip> Create(const char* filePath);
    static std::shared_ptr<AudioClip> Create(const gsl::span<const std::byte>& fileData);
    static std::shared_ptr<AudioClip> Create(const gsl::span<const std::byte>& fileData, AudioFormat audioFormat);
    gsl::span<std::byte> GetData() noexcept;
    gsl::span<const std::byte> GetData() const noexcept;
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

}
