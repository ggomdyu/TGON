/**
 * @file    OggVorbisAudioImporter.h
 * @author  ggomdyu
 * @since   04/20/2018
 */

#pragma once
#define TGON_USE_STB_OGG_VORBIS_IMPORTER 1
#if TGON_USE_STB_OGG_VORBIS_IMPORTER == 0
#   include <vorbis/vorbisfile.h>
#endif
#include <ogg/ogg.h>

#include "Diagnostics/Log.h"

#include "BaseAudioImporter.h"

#if TGON_USE_STB_OGG_VORBIS_IMPORTER
#   define STB_VORBIS_HEADER_ONLY
#   include <stb/stb_vorbis.c>
#endif

namespace tgon
{

struct OggVorbisFileStream final
{
/**@section Constructor */
public:
    OggVorbisFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept;

/**@section Method */
public:
    static size_t Read(void* buffer, size_t elementSize, size_t elementCount, void* stream);
    static int Seek(void* stream, ogg_int64_t offset, int origin);
    static int Close(void* stream);
    static long Tell(void* stream);

/**@section Variable */    
public:
    const uint8_t* srcData;
    const uint8_t* srcDataIter;
    size_t srcDataBytes;
};

inline OggVorbisFileStream::OggVorbisFileStream(const uint8_t* srcData, size_t srcDataBytes) noexcept :
    srcData(srcData),
    srcDataIter(srcData),
    srcDataBytes(srcDataBytes)
{
}

inline size_t OggVorbisFileStream::Read(void* buffer, size_t elementSize, size_t elementCount, void* stream)
{
    OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);
    
    size_t bytes = elementSize * elementCount;
    if (castedStream->srcDataIter + bytes > castedStream->srcData + castedStream->srcDataBytes)
    {
        bytes = castedStream->srcData + castedStream->srcDataBytes - castedStream->srcDataIter;
    }

    memcpy(buffer, castedStream->srcDataIter, bytes);
    castedStream->srcDataIter += bytes;

    return bytes;
}

inline int OggVorbisFileStream::Seek(void* stream, ogg_int64_t offset, int origin)
{
    OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);

    if (origin == SEEK_CUR)
    {
        castedStream->srcDataIter += offset;
    }
    else if (origin == SEEK_END)
    {
        castedStream->srcDataIter = castedStream->srcData + castedStream->srcDataBytes - offset;
    }
    else if (origin == SEEK_SET)
    {
        castedStream->srcDataIter = castedStream->srcData + offset;
    }
    else
    {
        return -1;
    }

    if (castedStream->srcDataIter < castedStream->srcData)
    {
        castedStream->srcDataIter = castedStream->srcData;
        return -1;
    }

    if (castedStream->srcDataIter > castedStream->srcData + castedStream->srcDataBytes)
    {
        castedStream->srcDataIter = castedStream->srcData + castedStream->srcDataBytes;
        return -1;
    }

    return 0;
}

inline int OggVorbisFileStream::Close(void* stream)
{
    return 0;
}

inline long OggVorbisFileStream::Tell(void* stream)
{
    const OggVorbisFileStream* castedStream = reinterpret_cast<OggVorbisFileStream*>(stream);
    return castedStream->srcDataIter - castedStream->srcData;
}

class OggVorbisAudioImporter :
    public BaseAudioImporter<OggVorbisAudioImporter>
{
/**@section Constructor */
public:
    using BaseAudioImporter<OggVorbisAudioImporter>::BaseAudioImporter;

/**@section Method */
public:
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);

private:
#if TGON_USE_STB_OGG_VORBIS_IMPORTER == 0
    ov_callbacks MakeCustomIOCallback() const noexcept;
    unsigned long DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, ogg_int64_t bufferSize, int channels);
#endif
};

inline bool OggVorbisAudioImporter::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    m_bitsPerSample = 16; // ogg vorbis is always 16 bit.

#if TGON_USE_STB_OGG_VORBIS_IMPORTER
    short* audioData = nullptr;
    auto audioDataBytes = stb_vorbis_decode_memory(srcData, srcDataBytes, &m_channels, &m_samplingRate, &audioData);
    m_audioData.reset(reinterpret_cast<uint8_t*>(audioData));
    m_audioDataBytes = audioDataBytes * 4;
#else
    OggVorbisFileStream fileStream(srcData, srcDataBytes);
    ov_callbacks ovCallbacks = this->MakeCustomIOCallback();

    OggVorbis_File oggVorbisFile;
    auto errorCode = ov_open_callbacks(reinterpret_cast<void*>(&fileStream), &oggVorbisFile, nullptr, -1, ovCallbacks);
    if (errorCode != 0)
    {
        Log(LogLevel::Debug, "Failed to invoke ov_open_callbacks. (Code: %d)", errorCode);
        return false;
    }

    const vorbis_info* vorbisInfo = ov_info(&oggVorbisFile, -1);
    if (vorbisInfo == nullptr)
    {
        Log(LogLevel::Debug, "Failed to invoke ov_info.");
        return false;
    }

    m_samplingRate = static_cast<int32_t>(vorbisInfo->rate);
    m_channels = vorbisInfo->channels;

    auto audioDataBytes = ov_pcm_total(&oggVorbisFile, -1) * 2 * static_cast<int64_t>(this->m_channels);
    m_audioData.reset(new uint8_t[(int)audioDataBytes]);
    m_audioDataBytes = static_cast<size_t>(audioDataBytes);

    DecodeOggVorbis(&oggVorbisFile, &m_audioData[0], audioDataBytes, vorbisInfo->channels);

    ov_clear(&oggVorbisFile);
#endif

    return true;
}

inline bool OggVorbisAudioImporter::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 16)
    {
        return false;
    }

    return true;
}

#if TGON_USE_STB_OGG_VORBIS_IMPORTER == 0
inline ov_callbacks OggVorbisAudioImporter::MakeCustomIOCallback() const noexcept
{
    ov_callbacks ovCallbacks;

    ovCallbacks.read_func = OggVorbisFileStream::Read;
    ovCallbacks.seek_func = OggVorbisFileStream::Seek;
    ovCallbacks.close_func = OggVorbisFileStream::Close;
    ovCallbacks.tell_func = OggVorbisFileStream::Tell;

    return ovCallbacks;
}

inline unsigned long OggVorbisAudioImporter::DecodeOggVorbis(OggVorbis_File* oggVorbisFile, uint8_t* destDecodeBuffer, ogg_int64_t bufferSize, int channels)
{
    int currentSection;

    unsigned long bytesDone = 0;
    while (true)
    {
        auto decodeSize = ov_read(oggVorbisFile, reinterpret_cast<char*>(destDecodeBuffer + bytesDone), static_cast<int>(bufferSize - bytesDone), 0, 2, 1, &currentSection);
        if (decodeSize > 0)
        {
            bytesDone += decodeSize;
            if (bytesDone >= bufferSize)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    // Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
    // however 6-Channels files need to be re-ordered
    if (channels == 6)
    {		
        uint16_t* samples = reinterpret_cast<uint16_t*>(destDecodeBuffer);
        for (unsigned long ulSamples = 0; ulSamples < (bufferSize >> 1); ulSamples += 6)
        {
            // WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
            // OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
            std::swap(samples[ulSamples+1], samples[ulSamples+2]);
            std::swap(samples[ulSamples+3], samples[ulSamples+5]);
            std::swap(samples[ulSamples+4], samples[ulSamples+5]);
        }
    }

    return bytesDone;
}
#endif

} /* namespace tgon */
