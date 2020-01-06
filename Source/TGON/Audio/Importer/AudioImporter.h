/**
 * @file    AudioImporter.h
 * @author  ggomdyu
 * @since   05/02/2018
 */

#pragma once
#include <cstdint>
#include <memory>
#include <gsl/span>

#include "Core/NonCopyable.h"

namespace tgon
{

class AudioImporter :
    private NonCopyable
{
/**@section Constructor */
public:
    AudioImporter() noexcept = default;

/**@section Method */
public:
    virtual bool Initialize(const gsl::span<const std::byte>& fileData) = 0;
    std::unique_ptr<std::byte[]>& GetAudioData() noexcept;
    const std::unique_ptr<std::byte[]>& GetAudioData() const noexcept;
    int32_t GetAudioDataBytes() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/**@section Variable */
protected:
    std::unique_ptr<std::byte[]> m_audioData;
    int32_t m_audioDataBytes = 0;
    int32_t m_bitsPerSample = 0;
    int32_t m_channels = 0;
    int32_t m_samplingRate = 0;
};

inline std::unique_ptr<std::byte[]>& AudioImporter::GetAudioData() noexcept
{
    return m_audioData;
}

inline const std::unique_ptr<std::byte[]>& AudioImporter::GetAudioData() const noexcept
{
    return m_audioData;
}

inline int32_t AudioImporter::GetAudioDataBytes() const noexcept
{
    return m_audioDataBytes;
}

inline int32_t AudioImporter::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

inline int32_t AudioImporter::GetChannels() const noexcept
{
    return m_channels;
}

inline int32_t AudioImporter::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

} /* namespace tgon */
