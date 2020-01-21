#include "PrecompiledHeader.h"

#include <stb_vorbis.c>

#include "WavAudioDecoder.h"
#include "RiffReader.h"

namespace tgon
{

std::optional<WavAudioDecoder> WavAudioDecoder::Create(const gsl::span<const std::byte>& fileData)
{
    if (WavAudioDecoder::IsWav(fileData) == false)
    {
        return {};
    }

    std::shared_ptr<std::byte[]> audioData;
    int32_t audioDataBytes = 0;
    int32_t bitsPerSample = 0;
    int32_t channels = 0;
    int32_t samplingRate = 0;
    
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
                
                channels = static_cast<decltype(m_channels)>(chunkData->channels);
                samplingRate = chunkData->samplingRate;
                bitsPerSample = chunkData->bitsPerSample;
            }
            break;

        case RiffReader::ChunkId::List:
            break;

        case RiffReader::ChunkId::Data:
            {
                auto chunkData = reinterpret_cast<const RiffReader::DataChunkData*>(chunkHeader.chunkData);
                
                audioDataBytes = chunkHeader.chunkDataSize;
                //audioData =
//                std::shared_ptr<std::byte[]>(new std::byte[chunkHeader.chunkDataSize]);

//                memcpy(&audioData[0], chunkData, chunkHeader.chunkDataSize);
            }
            break;
                
        default:
            break;
        }
    }
    while (riffReader.ReadNext());

    return WavAudioDecoder(std::move(audioData), audioDataBytes, bitsPerSample, channels, samplingRate);
}

bool WavAudioDecoder::IsWav(const gsl::span<const std::byte>& fileData)
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
