/**
 * @file    WavAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 * @see     https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include "../Generic/GenericAudioImporter.h"

#include "RiffReader.h"

namespace tgon
{

template <typename _AllocatorType>
class BasicWavAudioImporter final :
    public GenericAudioImporter<BasicWavAudioImporter<_AllocatorType>, _AllocatorType>
{
/* @section Public constructor */
public:
    using GenericAudioImporter<BasicWavAudioImporter<_AllocatorType>, _AllocatorType>::GenericAudioImporter;

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly Wav. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);

    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

template <typename _AllocatorType>
inline bool BasicWavAudioImporter<_AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
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
                
                this->m_channels = static_cast<decltype(this->m_channels)>(chunkData->channels);
                this->m_samplingRate = chunkData->samplingRate;
                this->m_bitsPerSample = chunkData->bitsPerSample;
            }
            break;

        case RiffReader::ChunkId::List:
            break;

        case RiffReader::ChunkId::Data:
            {
                auto chunkData = reinterpret_cast<const RiffReader::DataChunkData*>(chunkHeader.chunkData);
                
                this->m_audioData.resize(chunkHeader.chunkDataSize);
                memcpy(&this->m_audioData[0], chunkData, chunkHeader.chunkDataSize);
            }
            return true;
                
        default:
            break;
        }
    }
    while (riffReader.ReadNext());

    return true;
}

template <typename _AllocatorType>
inline bool BasicWavAudioImporter<_AllocatorType>::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
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
    
using WavAudioImporter = BasicWavAudioImporter<std::allocator<uint8_t>>;

} /* namespace tgon */
