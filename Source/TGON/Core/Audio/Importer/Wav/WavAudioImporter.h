/**
 * @filename    WavAudioImporter.h
 * @author      ggomdyu
 * @since       04/20/2018
 * @see         https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include <vector>
#include <cstdint>

#include "Core/Audio/Importer/Generic/GenericAudioImporter.h"

#include "RiffReader.h"

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class WavAudioImporter final :
    public GenericAudioImporter<WavAudioImporter<_AllocatorType>, _AllocatorType>
{
/* @section Public constructor */
public:
    using GenericAudioImporter::GenericAudioImporter;

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly WAV. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

template <typename _AllocatorType>
inline bool WavAudioImporter<_AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    RiffReader riffReader(srcData, srcDataBytes);
    do
    {
        RiffReader::ChunkHeader chunkHeader = riffReader.GetChunk();
        switch (chunkHeader.chunkId)
        {
        case RiffReader::ChunkID::Riff:
            break;

        case RiffReader::ChunkID::Fmt:
            {
                auto chunkData = reinterpret_cast<const RiffReader::FmtChunkData*>(chunkHeader.chunkData);
                
                m_channels = static_cast<decltype(m_channels)>(chunkData->channels);
                m_samplingRate = chunkData->samplingRate;
                m_bitsPerSample = chunkData->bitsPerSample;
            }
            break;

        case RiffReader::ChunkID::List:
            break;

        case RiffReader::ChunkID::Data:
            {
                auto chunkData = reinterpret_cast<const RiffReader::DataChunkData*>(chunkHeader.chunkData);
                
                m_soundData.resize(chunkHeader.chunkDataSize);
                memcpy(&m_soundData[0], chunkData, chunkHeader.chunkDataSize);
            }
            return true;
        }
    }
    while (riffReader.ReadNext());

    return true;
}

template <typename _AllocatorType>
inline bool WavAudioImporter<_AllocatorType>::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 16)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[0]) != RiffReader::ChunkID::Riff)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[8]) != RiffReader::ChunkID::Wave)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&srcData[12]) != RiffReader::ChunkID::Fmt)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */