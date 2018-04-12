/**
 * @filename    WAVImporter.h
 * @author      ggomdyu
 * @since       01/20/2018
 */

#pragma once
#include <vector>
#include <cstdint>

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class WAVImporter
{
/* @section Public constructor */
public:
    WAVImporter(const uint8_t* srcData, std::size_t srcDataBytes);

/* @section Private constructor */
private:
    WAVImporter() noexcept;

/* @section Public method */
public:
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
    bool IsValid() const noexcept;
    std::vector<uint8_t, _AllocatorType>& GetSoundData() noexcept;
    const std::vector<uint8_t, _AllocatorType>& GetSoundData() const noexcept;
    int32_t GetBitsPerSample() const noexcept;
    int32_t GetChannels() const noexcept;
    int32_t GetSamplingRate() const noexcept;

/* @section Private method */
private:
    /* @brief   Verifies the importing file is exactly WAV. */
    bool VerifyFormat(const uint8_t* srcData) const;

/* @section Private variable */
private:
    std::vector<uint8_t, _AllocatorType> m_soundData;
    int32_t m_bitsPerSample;
    int32_t m_channels;
    int32_t m_samplingRate;
};

template <typename _AllocatorType>
WAVImporter<_AllocatorType>::WAVImporter(const uint8_t * srcData, std::size_t srcDataBytes) :
    WAVImporter()
{
    this->Import(srcData, srcDataBytes);
}

template <typename _AllocatorType>
WAVImporter<_AllocatorType>::WAVImporter() noexcept :
    m_bitsPerSample(0),
    m_channels(0),
    m_samplingRate(0)
{
}

template <typename _AllocatorType>
bool WAVImporter<_AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (this->VerifyFormat(srcData) == false)
    {
        return false;
    }

    srcData += 16;

    int32_t chunkSize = *reinterpret_cast<const int32_t*>(srcData);
    srcData += sizeof(int32_t);

    int16_t formatType = *reinterpret_cast<const int16_t*>(srcData);
    srcData += sizeof(int16_t);

    m_channels = *reinterpret_cast<const int16_t*>(srcData);
    srcData += sizeof(int16_t);

    m_samplingRate = *reinterpret_cast<const int32_t*>(srcData);
    srcData += sizeof(int32_t);

    int32_t averageBytesPerSec = *reinterpret_cast<const int32_t*>(srcData);
    srcData += sizeof(int32_t);

    int16_t bytesPerSample = *reinterpret_cast<const int16_t*>(srcData);
    srcData += sizeof(int16_t);

    m_bitsPerSample = *reinterpret_cast<const int16_t*>(srcData);
    srcData += sizeof(int16_t);

    constexpr const char dataHeaderName[] = "data";
    if (strstr(reinterpret_cast<const char*>(srcData), dataHeaderName) == nullptr)
    {
        return false;
    }
    srcData += sizeof(dataHeaderName) - sizeof(dataHeaderName[0]);

    DWORD soundDataBytes = *reinterpret_cast<const int32_t*>(srcData);
    srcData += sizeof(int32_t);

    m_soundData.resize(soundDataBytes);
    memcpy(&m_soundData[0], srcData, soundDataBytes);

    return true;
}

template <typename _AllocatorType>
bool WAVImporter<_AllocatorType>::IsValid() const noexcept
{
    return m_soundData.size() > 0;
}

template <typename _AllocatorType>
bool WAVImporter<_AllocatorType>::VerifyFormat(const uint8_t* srcData) const
{
    if (strstr(reinterpret_cast<const char*>(&srcData[0]), "RIFF") == nullptr)
    {
        return false;
    }

    if (strstr(reinterpret_cast<const char*>(&srcData[8]), "WAVE") == nullptr)
    {
        return false;
    }

    if (strstr(reinterpret_cast<const char*>(&srcData[12]), "fmt ") == nullptr)
    {
        return false;
    }

    /*if (strstr(reinterpret_cast<const char*>(&srcData[36]), "data") == nullptr)
    {
        return false;
    }*/

    return true;
}

template <typename _AllocatorType>
std::vector<uint8_t, _AllocatorType>& WAVImporter<_AllocatorType>::GetSoundData() noexcept
{
    return m_soundData;
}

template <typename _AllocatorType>
const std::vector<uint8_t, _AllocatorType>& WAVImporter<_AllocatorType>::GetSoundData() const noexcept
{
    return m_soundData;
}

template <typename _AllocatorType>
int32_t WAVImporter<_AllocatorType>::GetBitsPerSample() const noexcept
{
    return m_bitsPerSample;
}

template <typename _AllocatorType>
inline int32_t WAVImporter<_AllocatorType>::GetChannels() const noexcept
{
    return m_channels;
}

template <typename _AllocatorType>
inline int32_t WAVImporter<_AllocatorType>::GetSamplingRate() const noexcept
{
    return m_samplingRate;
}

} /* namespace tgon */  
