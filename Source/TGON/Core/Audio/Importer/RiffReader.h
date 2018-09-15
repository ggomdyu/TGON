/**
 * @file    RiffReader.h
 * @author  ggomdyu
 * @since   05/03/2018
 */

#pragma once
#include <cstdint>

namespace tgon
{

class RiffReader
{
/**@section Public struct */
public:
    enum ChunkId : uint32_t
    {
//#if TGON_USING_LITTLE_ENDIAN
        Riff = 'FFIR',
        Wave = 'EVAW',
        Cue = ' euc',
        Fact = 'tcaf',
        Plst = 'tslp',
        Data = 'atad',
        Fmt = ' tmf',
        List = 'TSIL',
        Label = 'lbal',
        Ltxt = 'txtl',
        Note = 'eton',
        Smpl = 'lpms',
        Inst = 'tsni',
//#else
//#endif
    };

    struct ChunkHeader
    {
    /**@section Public constructor */
    public:
        ChunkHeader(ChunkId chunkId, uint32_t chunkDataSize, const uint8_t* chunkData) noexcept;
        
    /**@section Public method */
    public:
        std::size_t GetSize() const noexcept;
        
    /**@section Public variable */
    public:
        ChunkId chunkId;
        uint32_t chunkDataSize;
        const uint8_t* chunkData;
    };

    struct RIFFChunkData
    {
        uint32_t riffType;
    };

    struct FmtChunkData
    {
        enum class AudioFormat : int16_t
        {
            PCM = 0x0001,
            IEEEFloat = 0x0003,
            ALaw = 0x0006,
            MuLaw = 0x0007,
        };

        enum class AudioChannel : int16_t
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

/**@section Public type */
public:
    RiffReader(const uint8_t* srcData, std::size_t srcDataBytes) noexcept;
    
/**@section Public method */
public:
    bool ReadNext();
    ChunkHeader GetChunkHeader() const;

/**@section Private variable */
private:
    const uint8_t* m_srcData;
    const uint8_t* m_srcDataIter;
    std::size_t m_srcDataBytes;
};

inline RiffReader::ChunkHeader::ChunkHeader(ChunkId chunkId, uint32_t chunkDataSize, const uint8_t* chunkData) noexcept :
    chunkId(chunkId),
    chunkDataSize(chunkDataSize),
    chunkData(chunkData)
{
}
    
inline std::size_t RiffReader::ChunkHeader::GetSize() const noexcept
{
    auto chunkSize = sizeof(chunkId) + sizeof(chunkDataSize) + sizeof(uint32_t);
    if (chunkId != ChunkId::Riff)
    {
        chunkSize -= sizeof(uint32_t) - chunkDataSize;
    }
    
    return chunkSize;
}

inline RiffReader::RiffReader(const uint8_t* srcData, std::size_t srcDataBytes) noexcept :
    m_srcData(srcData),
    m_srcDataIter(srcData),
    m_srcDataBytes(srcDataBytes)
{
}

inline bool RiffReader::ReadNext()
{
    ChunkHeader currChunk = GetChunkHeader();

    m_srcDataIter += currChunk.GetSize();
    if (m_srcDataIter >= m_srcData + m_srcDataBytes) // This not works fine. Should be fixed!
    {
        return false;
    }

    return true;
}

inline RiffReader::ChunkHeader RiffReader::GetChunkHeader() const
{
    return ChunkHeader(static_cast<ChunkId>(*reinterpret_cast<const uint32_t*>(&m_srcDataIter[0])), *reinterpret_cast<const uint32_t*>(&m_srcDataIter[4]), &m_srcDataIter[8]);
}

} /* namespace tgon */
