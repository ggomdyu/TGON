/**
 * @filename    RiffReader.h
 * @author      ggomdyu
 * @since       05/03/2018
 */

#pragma once
#include <cstdint>

namespace tgon
{

class RiffReader
{
/* @section Public struct */
public:
    enum ChunkID : uint32_t
    {
        Riff = 'FFIR',
        Wave = 'EVAW',
        Xwma = 'AMWX',
        List = 'tsil',
        Data = 'atad',
        Fmt = ' tmf',
        Smpl = 'lpms',
    };

    struct ChunkHeader
    {
        ChunkID chunkId;
        uint32_t chunkDataSize;
        const uint8_t* chunkData;
    };

    struct RIFFChunkData
    {
        uint32_t riffType;
    };

    struct FmtChunkData
    {
        enum class AudioFormat : short
        {
            PCM = 0x0001,
            IEEEFloat = 0x0003,
            ALaw = 0x0006,
            MuLaw = 0x0007,
        };

        enum class AudioChannel : short
        {
            Mono = 1,
            Stereo = 2,
        };

        AudioFormat audioFormat;
        AudioChannel channels;
        int32_t samplingRate;
        int32_t avgBytesPerSec;     // samplingRate * channels * bitsPerSample / 8
        int16_t blockAlign;         // channels * bitsPerSample / 8
        int16_t bitsPerSample;
    };

    struct ListChunkData
    {
        uint32_t listType;
    };

    struct DataChunkData
    {
    };

/* @section Public type */
public:
    RiffReader(const uint8_t* srcData, uint32_t srcDataBytes) noexcept;
    
/* @section Public method */
public:
    bool ReadNext();
    ChunkHeader GetChunk() const;

/* @section Private variable */
private:
    const uint8_t* m_srcData;
    const uint8_t* m_srcDataIter;
    uint32_t m_srcDataBytes;
};

inline RiffReader::RiffReader(const uint8_t* srcData, uint32_t srcDataBytes) noexcept :
    m_srcData(srcData),
    m_srcDataIter(srcData),
    m_srcDataBytes(srcDataBytes)
{
}

inline bool RiffReader::ReadNext()
{
    ChunkHeader currChunk = GetChunk();

    auto moveOffset = sizeof(ChunkHeader);
    if (currChunk.chunkId != ChunkID::Riff)
    {
        moveOffset -= sizeof(currChunk.chunkData) - currChunk.chunkDataSize;
    }
        
    m_srcDataIter += moveOffset;
    if (m_srcDataIter >= m_srcData + m_srcDataBytes) // This not works fine. Should be fixed!
    {
        return false;
    }

    return true;
}

inline RiffReader::ChunkHeader RiffReader::GetChunk() const
{
    return ChunkHeader{
        static_cast<ChunkID>(*reinterpret_cast<const uint32_t*>(&m_srcDataIter[0])),
        *reinterpret_cast<const uint32_t*>(&m_srcDataIter[4]),
        &m_srcDataIter[8]
    };
}

} /* namespace tgon */