/**
 * @filename    WAVImporter.h
 * @author      ggomdyu
 * @since       04/20/2018
 * @see         https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#list
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include <vector>
#include <cstdint>

namespace tgon
{
namespace detail
{

class BasicWAVImporter
{
/* @section Protected enum */
protected:
    enum class WAVAudioFormat : short
    {
        PCM = 0x0001,
        IEEE_Float = 0x0003,
        ALaw = 0x0006,
        MuLaw = 0x0007,
    };

    enum class WAVAudioChannel : short
    {
        Mono = 1,
        Stereo = 2,
    };

/* @section Protected class */
protected:
    struct RIFFChunk
    {
        char chunkID[4];            // Contains "RIFF"
        int32_t chunkDataSize;
        char riffType[4];           // Contains "WAVE"
    };

    struct FmtChunk
    {
        char chunkID[4];            // Contains "fmt "
        int32_t chunkDataSize;
        WAVAudioFormat wavAudioFormat;
        WAVAudioChannel channels;
        int32_t samplingRate;
        int32_t avgBytesPerSec;     // sampleRate * channels * bitsPerSample / 8
        int16_t blockAlign;         // channels * bitsPerSample / 8
        int16_t bitsPerSample;
    };

    struct ListChunk
    {
        char chunkID[4];            // Contains "list"
        int32_t chunkDataSize;
        char typeID[4];             // Contains "adtl"
    };

    struct DataChunk
    {
        char chunkID[4];            // Contains "list"
        int32_t chunkDataSize;
    };

/* @section Protected constructor */
protected:
    BasicWAVImporter() {}
};

} /* namespace detail */

template <typename _AllocatorType = std::allocator<uint8_t>>
class WAVImporter :
    private detail::BasicWAVImporter
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

    const RIFFChunk* riffChunk = reinterpret_cast<const RIFFChunk*>(srcData);
    
    const char* chunks = reinterpret_cast<const char*>(riffChunk) + sizeof(*riffChunk);
    while (true)
    {
        if (strstr(chunks, "fmt ") != nullptr || strstr(chunks, "FMT ") != nullptr)
        {
            const FmtChunk* fmtChunk = reinterpret_cast<const FmtChunk*>(chunks);

            m_channels = static_cast<decltype(m_channels)>(fmtChunk->channels);
            m_samplingRate = fmtChunk->samplingRate;
            m_bitsPerSample = fmtChunk->bitsPerSample;

            chunks += sizeof(FmtChunk);
        }

        if (strstr(chunks, "list") != nullptr || strstr(chunks, "LIST") != nullptr)
        {
            auto listChunk = reinterpret_cast<const ListChunk*>(chunks);

            chunks += listChunk->chunkDataSize + 8;
        }
        
        if (strstr(chunks, "data") != nullptr || strstr(chunks, "DATA") != nullptr)
        {
            auto dataChunk = reinterpret_cast<const DataChunk*>(chunks);

            m_soundData.resize(dataChunk->chunkDataSize);
            memcpy(&m_soundData[0], reinterpret_cast<const uint8_t*>(dataChunk) + sizeof(DataChunk), dataChunk->chunkDataSize);

            break;
        }
    }

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