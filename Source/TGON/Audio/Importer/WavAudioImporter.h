/**
 * @file    WavAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 * @see     https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include "BaseAudioImporter.h"
#include "RiffReader.h"

namespace tgon
{

class WavAudioImporter final :
    public BaseAudioImporter<WavAudioImporter>
{
/**@section Constructor */
public:
    using BaseAudioImporter<WavAudioImporter>::BaseAudioImporter;

/**@section Method */
public:
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

inline bool WavAudioImporter::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    RiffReader riffReader(srcData, srcDataBytes);
    do
    {
        RiffReader::ChunkHeader chunkHeader = riffReader.GetChunkHeader();
        switch (chunkHeader.chunkId)
        {
        case RiffReader::ChunkId::Riff:
            break;

        case RiffReader::ChunkId::Fmt:
            {
                auto chunkData = reinterpret_cast<const RiffReader::FmtChunkData*>(chunkHeader.chunkData);
                
                m_channels = static_cast<decltype(m_channels)>(chunkData->channels);
                m_samplingRate = chunkData->samplingRate;
                m_bitsPerSample = chunkData->bitsPerSample;
            }
            break;

        case RiffReader::ChunkId::List:
            break;

        case RiffReader::ChunkId::Data:
            {
                auto chunkData = reinterpret_cast<const RiffReader::DataChunkData*>(chunkHeader.chunkData);
                
                m_audioDataBytes = chunkHeader.chunkDataSize;
                m_audioData.reset(new uint8_t[chunkHeader.chunkDataSize]);

                memcpy(&m_audioData[0], chunkData, chunkHeader.chunkDataSize);
            }
            return true;
                
        default:
            break;
        }
    }
    while (riffReader.ReadNext());

    return true;
}

inline bool WavAudioImporter::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 16)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[0]) != RiffReader::ChunkId::Riff)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[8]) != RiffReader::ChunkId::Wave)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[12]) != RiffReader::ChunkId::Fmt)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
