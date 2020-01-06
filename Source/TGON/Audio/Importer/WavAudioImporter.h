/**
 * @file    WavAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 * @see     https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
 *              http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */

#pragma once
#include "AudioImporter.h"
#include "RiffReader.h"

namespace tgon
{

class WavAudioImporter final :
    public AudioImporter
{
/**@section Method */
public:
    static bool IsExactFormat(const gsl::span<const std::byte>& fileData);
    bool Initialize(const gsl::span<const std::byte>& fileData) override;
};

inline bool WavAudioImporter::Initialize(const gsl::span<const std::byte>& fileData)
{
    if (WavAudioImporter::IsExactFormat(fileData) == false)
    {
        return false;
    }

    RiffReader riffReader(fileData.data(), fileData.size());
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
                m_audioData.reset(new std::byte[chunkHeader.chunkDataSize]);

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

inline bool WavAudioImporter::IsExactFormat(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 16)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&fileData[0]) != RiffReader::ChunkId::Riff)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&fileData[8]) != RiffReader::ChunkId::Wave)
    {
        return false;
    }

    if (*reinterpret_cast<const uint32_t*>(&fileData[12]) != RiffReader::ChunkId::Fmt)
    {
        return false;
    }

    return true;
}

} /* namespace tgon */
